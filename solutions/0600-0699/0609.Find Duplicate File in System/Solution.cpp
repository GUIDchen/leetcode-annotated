// 题目：609. 在系统中查找重复文件（Find Duplicate File in System）
// 思路：按空格切分每条目录记录，解析出「文件名(内容)」并把内容相同的完整路径收集到同一个哈希桶里。
// 时间复杂度：O(L)，L 为所有字符串的总长度；空间复杂度：O(L)，哈希表保存所有文件的路径与内容。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<string>> findDuplicate(vector<string>& paths) {  // paths 是形如「目录 文件1(内容1) 文件2(内容2)」的字符串列表
        unordered_map<string, vector<string>> d;  // 哈希表：键是文件内容，值是该内容对应的全部文件绝对路径
        for (auto& p : paths) {  // 逐条处理一个目录及其下属文件
            auto ps = split(p, ' ');  // 按空格切分，第 0 项是目录，其余每项是「文件名(内容)」
            for (int i = 1; i < ps.size(); ++i) {  // 下标 0 是目录名，所以从 1 开始遍历文件项
                int j = ps[i].find('(');  // 定位左括号，它前面是文件名、后面是文件内容
                auto content = ps[i].substr(j + 1, ps[i].size() - j - 2);  // 取出括号内的内容，长度要再减去左右括号各一个字符
                auto name = ps[0] + '/' + ps[i].substr(0, j);  // 把目录与文件名用斜杠拼成完整路径
                d[content].push_back(name);  // 按内容分组，内容相同的文件路径会进入同一个桶
            }  // 当前目录的文件处理完毕
        }  // 所有目录记录处理完毕
        vector<vector<string>> ans;  // 存放最终答案：每一组都是一批内容相同的文件路径
        for (auto& [_, e] : d) {  // 结构化绑定遍历哈希表，忽略内容（键），只关心路径分组（值）
            if (e.size() > 1) {  // 只有至少两个文件共享同一内容才算重复
                ans.push_back(e);  // 把这一组重复文件整体加入答案
            }  // 分组判断结束
        }  // 哈希表遍历结束
        return ans;  // 返回所有重复文件分组
    }  // 主方法结束

    vector<string> split(string& s, char c) {  // 辅助函数：按分隔符 c 切分字符串 s
        vector<string> res;  // 保存切分出来的各个片段
        stringstream ss(s);  // 用字符串流配合 getline 完成切分
        string t;  // 临时变量，承接每次读到的一段
        while (getline(ss, t, c)) {  // 反复读取到分隔符为止，流耗尽时结束
            res.push_back(t);  // 把当前片段追加到结果中
        }  // 切分循环结束
        return res;  // 返回全部片段
    }  // 辅助函数结束
};  // 类定义结束