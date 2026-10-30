// 题目：1233. 删除子文件夹（Remove Sub-Folders from the Filesystem）
// 思路：先按字典序排序，父文件夹必在子文件夹之前；用已保留的最后一个路径做前缀匹配，判断当前路径是否为子文件夹。
// 时间复杂度：O(n log n + n·L)，排序与逐条前缀比较；空间复杂度：O(n)，存放结果列表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> removeSubfolders(vector<string>& folder) {  // folder 是所有文件夹路径，返回去掉子文件夹后的列表
        sort(folder.begin(), folder.end());  // 字典序排序：父文件夹一定排在它所有子文件夹之前
        vector<string> ans = {folder[0]};  // 第一个路径不可能成为别人的子文件夹，直接作为初始答案
        for (int i = 1; i < folder.size(); ++i) {  // 从第二个路径开始逐个判断
            int m = ans.back().size();  // 最近保留的文件夹长度，它是最可能成为前缀的候选
            int n = folder[i].size();  // 当前待判断路径的长度
            if (m >= n || !(ans.back() == folder[i].substr(0, m) && folder[i][m] == '/')) {  // m >= n 时短路避免下标越界；否则要求「前缀 + '/'」才认定是子文件夹
                ans.emplace_back(folder[i]);  // 不是子文件夹，保留它
            }  // if 结束
        }  // for 结束
        return ans;  // 返回过滤后的文件夹列表
    }  // 方法结束
};  // 类定义结束