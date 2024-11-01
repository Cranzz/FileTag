#ifndef FILE_TAG_SYSTEM_H
#define FILE_TAG_SYSTEM_H

#include <string>
#include <vector>

#include "TagManager.h"
#include "UserManager.h"

class FileTagSystem {
public:
    // 构造函数，接受标签文件路径作为参数
    explicit FileTagSystem(const std::string& tagsFile, const std::string& usersFile);
    // 主运行函数，控制程序的主循环
    void run();

    // 添加标签的函数
    void addTags(const std::string& filepath, const std::string& tag);
    // 根据标签搜索文件的函数
    std::vector<std::string> searchFilesByTag(const std::string& tag) const;
    // 删除标签的函数
    void removeTag(const std::string& filepath, const std::string& tag);
    // 更新标签的函数
    void updateTag(const std::string& filepath, const std::string& oldTag, const std::string& newTag);
    // 列出所有标签的函数
    std::vector<std::string> listAllTags() const;

private:
    // 显示主菜单
    void displayMenu() const;
    // 处理用户的菜单选择
    void handleChoice(int choice);

    // 列出某个文件的所有标签的函数
    void listTagsForFile() const;

    // 新增的用户登录和管理函数
    bool login();
    void displayAdminMenu() const;
    void handleAdminChoice(int choice);

    TagManager tagManager;
    UserManager userManager;  // 用户管理对象
    std::string currentUser;  // 当前用户名
    UserRole currentUserRole; // 当前用户角色

    // 获取有效用户输入的函数，带有提示信息
    std::string getValidInput(const std::string& prompt) const;
    // 获取标签输入的函数
    std::string getTag() const;
    // 获取有效路径输入的函数
    std::string getValidPath() const;
};

#endif // FILE_TAG_SYSTEM_H
