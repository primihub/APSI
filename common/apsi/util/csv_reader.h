// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#pragma once

// STD
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

// APSI
#include "apsi/item.h"
#include "apsi/psi_params.h"
#include "apsi/util/db_encoding.h"

namespace apsi {
namespace util {
/**
Simple CSV file parser
*/
class CSVReader {
public:
    using UnlabeledData = std::vector<apsi::Item>;

    using LabeledData = std::vector<std::pair<apsi::Item, apsi::Label>>;

    using DBData = std::variant<UnlabeledData, LabeledData>;

    CSVReader();

    CSVReader(const std::string &file_name);

    std::pair<DBData, std::vector<std::string>> read(std::istream &stream);

    std::pair<DBData, std::vector<std::string>> read();

protected:
    std::pair<std::map<std::string, std::string>, bool> pre_process(std::istream& stream);
    std::pair<bool, bool> process_line( const std::string& line,
            std::string& item,
            std::string& label);
private:
    std::string file_name_;

    std::pair<bool, bool> process_line(
        const std::string &line,
        std::string &orig_item,
        apsi::Item &item,
        apsi::Label &label) const;
}; // class CSVReader
}
}
