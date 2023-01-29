// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

// STD
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <utility>

// APSI
#include "apsi/log.h"
#include "apsi/util/common_utils.h"
#include "apsi/util/csv_reader.h"

using namespace std;
using namespace apsi;
//using namespace apsi::util;

namespace apsi {
namespace util {
CSVReader::CSVReader()
{}

CSVReader::CSVReader(const string &file_name) : file_name_(file_name)
{
    throw_if_file_invalid(file_name_);
}

auto CSVReader::read(istream &stream) -> pair<DBData, vector<string>>
{
    string line;
    DBData result;
    vector<string> orig_items;

    if (!getline(stream, line)) {
        APSI_LOG_WARNING("Nothing to read in `" << file_name_ << "`");
        return { UnlabeledData{}, {} };
    } else {
        string orig_item;
        Item item;
        Label label;
        auto [has_item, has_label] = process_line(line, orig_item, item, label);

        if (!has_item) {
            APSI_LOG_WARNING("Failed to read item from `" << file_name_ << "`");
            return { UnlabeledData{}, {} };
        }

        orig_items.push_back(move(orig_item));
        if (has_label) {
            result = LabeledData{ make_pair(move(item), move(label)) };
        } else {
            result = UnlabeledData{ move(item) };
        }
    }

    while (getline(stream, line)) {
        string orig_item;
        Item item;
        Label label;
        auto [has_item, _] = process_line(line, orig_item, item, label);

        if (!has_item) {
            // Something went wrong; skip this item and move on to the next
            APSI_LOG_WARNING("Failed to read item from `" << file_name_ << "`");
            continue;
        }

        orig_items.push_back(move(orig_item));
        if (holds_alternative<UnlabeledData>(result)) {
            get<UnlabeledData>(result).push_back(move(item));
        } else if (holds_alternative<LabeledData>(result)) {
            get<LabeledData>(result).push_back(make_pair(move(item), move(label)));
        } else {
            // Something is terribly wrong
            APSI_LOG_ERROR("Critical error reading data");
            throw runtime_error("variant is in bad state");
        }
    }

    return { move(result), move(orig_items) };
}


auto CSVReader::read() -> pair<DBData, vector<string>>
{
    throw_if_file_invalid(file_name_);

    ifstream file(file_name_);
    if (!file.is_open()) {
        APSI_LOG_ERROR("File `" << file_name_ << "` could not be opened for reading");
        throw runtime_error("could not open file");
    }

    // return read(file);
    auto processed_data_info = pre_process(file);
    auto& processed_data = std::get<0>(processed_data_info);
    auto is_labeled_data = std::get<1>(processed_data_info);
    DBData result;
    std::vector<std::string> origin_item;
    if (is_labeled_data) {
        LabeledData labeled_data;
        labeled_data.reserve(processed_data.size());
        origin_item.reserve(processed_data.size());
        for (auto& item_info : processed_data) {
            auto& item_str = item_info.first;
            auto& label_str = item_info.second;
            origin_item.push_back(item_str);
            Item item = item_str;
            Label label;
            label.reserve(label_str.size());
            copy(label_str.begin(), label_str.end(), back_inserter(label));
            labeled_data.push_back(make_pair(move(item), move(label)));
        }
        result = std::move(labeled_data);
    } else {
        UnlabeledData unlabled_data;
        unlabled_data.reserve(processed_data.size());
        origin_item.reserve(processed_data.size());
        for (auto& item_info : processed_data) {
            auto& item_str = item_info.first;
            origin_item.push_back(item_str);
            Item item = item_str;
            unlabled_data.push_back(move(item));
        }
        result = std::move(unlabled_data);
    }
    return { move(result), move(origin_item) };
}

std::pair<std::map<std::string, std::string>, bool>
CSVReader::pre_process(std::istream& stream) {
    string line;
    bool is_labeled_data{false};
    std::map<std::string, std::string> processed_data;
    if (!getline(stream, line)) {
        APSI_LOG_WARNING("Nothing to read in `" << file_name_ << "`");
        return {processed_data, false};
    } else {
        std::string item;
        std::string label;
        auto [has_item, has_label] = process_line(line, item, label);
        if (has_item) {
            std::string _label;
            if (has_label) {
                _label = std::move(label);
                is_labeled_data = true;
            }
            processed_data.insert({std::move(item), std::move(_label)});
        }
    }

    if (is_labeled_data) {
        std::string item;
        std::string label;
        while (getline(stream, line)) {
            auto [has_item, _] = process_line(line, item, label);
            if (!has_item) {
                // Something went wrong; skip this item and move on to the next
                APSI_LOG_WARNING("Failed to read item from `" << file_name_ << "`");
                continue;
            }
            auto it = processed_data.find(item);
            if ( it != processed_data.end()) {
                // duplicate data
                auto& label_ = it->second;
                label_.append("#####").append(std::move(label));
            } else {
                processed_data.insert({std::move(item), std::move(label)});
            }
        }
    } else {
        std::string item;
        std::string label;
        while (getline(stream, line)) {
            auto [has_item, _] = process_line(line, item, label);
            if (!has_item) {
                // Something went wrong; skip this item and move on to the next
                APSI_LOG_WARNING("Failed to read item from `" << file_name_ << "`");
                continue;
            }
            auto it = processed_data.find(item);
            if ( it != processed_data.end()) {
                continue;
            } else {
                processed_data.insert({std::move(item), std::string("")});
            }
        }
    }
    return {std::move(processed_data), is_labeled_data};
}

std::pair<bool, bool> CSVReader::process_line( const std::string& line,
        std::string& item, std::string& label) {
//
    stringstream ss(line);
    string token;

    // First is the item
    getline(ss, token, ',');
    // Trim leading whitespace
    token.erase(
        token.begin(), find_if(token.begin(), token.end(), [](int ch) { return !isspace(ch); }));

    // Trim trailing whitespace
    token.erase(
        find_if(token.rbegin(), token.rend(), [](int ch) { return !isspace(ch); }).base(),
        token.end());

    if (token.empty()) {
        // Nothing found
        return { false, false };
    }
    // Item can be of arbitrary length; the constructor of Item will automatically hash it
    item = std::move(token);

    // Second is the label
    token.clear();
    getline(ss, token);

    // Trim leading whitespace
    token.erase(
        token.begin(), find_if(token.begin(), token.end(), [](int ch) { return !isspace(ch); }));

    // Trim trailing whitespace
    token.erase(
        find_if(token.rbegin(), token.rend(), [](int ch) { return !isspace(ch); }).base(),
        token.end());

    label.clear();
    label = std::move(token);

    return {true, !label.empty() };
}


pair<bool, bool> CSVReader::process_line(
    const string &line, string &orig_item, Item &item, Label &label) const
{
    stringstream ss(line);
    string token;

    // First is the item
    getline(ss, token, ',');

    // Trim leading whitespace
    token.erase(
        token.begin(), find_if(token.begin(), token.end(), [](int ch) { return !isspace(ch); }));

    // Trim trailing whitespace
    token.erase(
        find_if(token.rbegin(), token.rend(), [](int ch) { return !isspace(ch); }).base(),
        token.end());

    if (token.empty()) {
        // Nothing found
        return { false, false };
    }

    // Item can be of arbitrary length; the constructor of Item will automatically hash it
    orig_item = token;
    item = token;

    // Second is the label
    token.clear();
    getline(ss, token);

    // Trim leading whitespace
    token.erase(
        token.begin(), find_if(token.begin(), token.end(), [](int ch) { return !isspace(ch); }));

    // Trim trailing whitespace
    token.erase(
        find_if(token.rbegin(), token.rend(), [](int ch) { return !isspace(ch); }).base(),
        token.end());

    label.clear();
    label.reserve(token.size());
    copy(token.begin(), token.end(), back_inserter(label));

    return { true, !token.empty() };
}
}
}
