#include "tag_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdexcept>
#include <unordered_set>
#include <algorithm> // ���� algorithm ͷ�ļ���ʹ�� std::find �� std::remove

TagManager::TagManager(const std::string& filename) : filename(filename) {}

void TagManager::loadTags() {
    std::ifstream infile(filename);
    std::string line;

    if (!infile.is_open()) {
        std::cerr << "�޷����ļ� " << filename << "��������һ���µ��ļ���" << std::endl;
        std::ofstream outfile(filename); // ����һ���µ�CSV�ļ�
        if (!outfile.is_open()) {
            throw std::runtime_error("�޷������ļ� " + filename);
        }
        outfile.close();
        return;
    }

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string filepath, tag;
        if (std::getline(iss, filepath, ',')) {
            std::vector<std::string> fileTags;
            while (std::getline(iss, tag, ',')) {
                fileTags.push_back(tag);
            }
            tags[filepath] = fileTags;
        }
    }
}

void TagManager::saveTags() const {
    std::ofstream outfile(filename);

    if (!outfile.is_open()) {
        throw std::runtime_error("�޷����ļ� " + filename);
    }

    for (const auto& [filepath, fileTags] : tags) {
        outfile << filepath;
        for (const auto& tag : fileTags) {
            outfile << "," << tag;
        }
        outfile << std::endl;
    }
}

void TagManager::addTag(const std::string& filepath, const std::string& tag) {
    if (std::find(tags[filepath].begin(), tags[filepath].end(), tag) == tags[filepath].end()) {
        tags[filepath].push_back(tag);
    }
}

void TagManager::removeTag(const std::string& filepath, const std::string& tag) {
    auto& fileTags = tags[filepath];
    fileTags.erase(std::remove(fileTags.begin(), fileTags.end(), tag), fileTags.end());
}

void TagManager::updateTag(const std::string& filepath, const std::string& oldTag, const std::string& newTag) {
    auto it = std::find(tags[filepath].begin(), tags[filepath].end(), oldTag);
    if (it != tags[filepath].end()) {
        *it = newTag;
    }
}

std::vector<std::string> TagManager::searchFilesByTag(const std::string& tag) const {
    std::vector<std::string> filepaths;
    for (const auto& [filepath, fileTags] : tags) {
        if (std::find(fileTags.begin(), fileTags.end(), tag) != fileTags.end()) {
            filepaths.push_back(filepath);
        }
    }
    return filepaths;
}

std::vector<std::string> TagManager::listAllTags() const {
    std::unordered_set<std::string> allTags;
    for (const auto& [filepath, fileTags] : tags) {
        allTags.insert(fileTags.begin(), fileTags.end());
    }
    return std::vector<std::string>(allTags.begin(), allTags.end());
}

std::vector<std::string> TagManager::listTagsForFile(const std::string& filepath) const {
    if (tags.find(filepath) != tags.end()) {
        return tags.at(filepath);
    }
    return {};
}

std::string getValidPath() {
    std::string path;
    while (true) {
        std::cout << "�������ļ����ļ���·��: ";
        std::cout.flush();  // ����ˢ�»�����
        std::cin >> path;

        // ���·���Ƿ����
        if (std::filesystem::exists(path)) {
            break;
        } else {
            std::cerr << "·��������: " << path << std::endl;
            std::cout.flush(); // ����ˢ�»�����
        }
    }
    return path;
}

std::string getTag() {
    std::string tag;
    std::cout << "������Ҫ��ӵı�ǩ (���� 'exit' �˳���������): ";
    std::cout.flush();  // ����ˢ�»�����
    std::cin >> tag;
    return tag;
}
