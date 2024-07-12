#include "tag_manager.h"
#include <iostream>
#include <filesystem>

int main() {
    // �� std::cerr �ض��� std::cout
    std::cerr.rdbuf(std::cout.rdbuf());

    const std::string tagsFile = "tags.csv";
    std::cout << "��ǩ�ļ�·��: " << tagsFile << std::endl;
    std::cout.flush();  // ����ˢ�»�����

    TagManager tagManager(tagsFile);
    try {
        tagManager.loadTags();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    while (true) {
        int choice;
        std::cout << "��ѡ�������\n1. ��ӱ�ǩ\n2. ���ݱ�ǩ�����ļ�\n3. ɾ����ǩ\n4. ���±�ǩ\n5. �鿴���б�ǩ\n6. �鿴ĳ���ļ��ı�ǩ\n7. �˳�" << std::endl;
        std::cin >> choice;

        if (choice == 1) {
            std::string path = getValidPath();

            if (std::filesystem::is_directory(path)) {
                int tagChoice;
                std::cout << "��ѡ�������1. �������ļ������ͬ�ı�ǩ 2. ÿ���ļ�������ӱ�ǩ" << std::endl;
                std::cin >> tagChoice;

                if (tagChoice == 1) {
                    std::string tag = getTag();
                    if (tag == "exit") {
                        continue;
                    }
                    for (const auto& entry : std::filesystem::directory_iterator(path)) {
                        if (entry.is_regular_file()) {
                            tagManager.addTag(entry.path().string(), tag);
                        }
                    }
                } else if (tagChoice == 2) {
                    for (const auto& entry : std::filesystem::directory_iterator(path)) {
                        if (entry.is_regular_file()) {
                            std::cout << "�ļ�: " << entry.path().string() << std::endl;
                            std::string tag = getTag();
                            if (tag == "exit") {
                                try {
                                    tagManager.saveTags();
                                } catch (const std::exception& e) {
                                    std::cerr << e.what() << std::endl;
                                    return 1;
                                }
                                std::cout << "�ѱ��浱ǰ���ݣ����������档" << std::endl;
                                break;
                            }
                            tagManager.addTag(entry.path().string(), tag);
                        }
                    }
                } else {
                    std::cerr << "��Ч��ѡ��" << std::endl;
                    continue;
                }
            } else {
                std::string tag = getTag();
                if (tag == "exit") {
                    continue;
                }
                tagManager.addTag(path, tag);
            }

            try {
                tagManager.saveTags();
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                return 1;
            }
            std::cout << "��ǩ��ӳɹ���" << std::endl;
        } else if (choice == 2) {
            std::string tag = getTag();
            if (tag == "exit") {
                continue;
            }
            std::vector<std::string> filepaths = tagManager.searchFilesByTag(tag);
            if (filepaths.empty()) {
                std::cout << "û���ҵ�ƥ����ļ���" << std::endl;
            } else {
                std::cout << "ƥ����ļ�·����" << std::endl;
                for (const auto& filepath : filepaths) {
                    std::cout << filepath << std::endl;
                }
            }
        } else if (choice == 3) {
            std::string path = getValidPath();
            std::string tag = getTag();
            if (tag == "exit") {
                continue;
            }
            tagManager.removeTag(path, tag);

            try {
                tagManager.saveTags();
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                return 1;
            }
            std::cout << "��ǩɾ���ɹ���" << std::endl;
        } else if (choice == 4) {
            std::string path = getValidPath();
            std::string oldTag = getTag();
            if (oldTag == "exit") {
                continue;
            }
            std::cout << "�������µı�ǩ: ";
            std::string newTag;
            std::cin >> newTag;
            tagManager.updateTag(path, oldTag, newTag);

            try {
                tagManager.saveTags();
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                return 1;
            }
            std::cout << "��ǩ���³ɹ���" << std::endl;
        } else if (choice == 5) {
            auto tags = tagManager.listAllTags();
            std::cout << "���б�ǩ��" << std::endl;
            for (const auto& tag : tags) {
                std::cout << tag << std::endl;
            }
        } else if (choice == 6) {
            std::string path = getValidPath();
            auto tags = tagManager.listTagsForFile(path);
            std::cout << "�ļ� " << path << " �ı�ǩ��" << std::endl;
            for (const auto& tag : tags) {
                std::cout << tag << std::endl;
            }
        } else if (choice == 7) {
            std::cout << "�˳�����" << std::endl;
            break;
        } else {
            std::cerr << "��Ч��ѡ��" << std::endl;
        }
    }

    return 0;
}
