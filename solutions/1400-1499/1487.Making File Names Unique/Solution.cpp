// 题目：1487. 保证文件名唯一（Making File Names Unique）
// 核心思路：哈希表记录每个名字已用到的后缀编号，重名时从该编号起递增试探，直到找到未占用的名字。
// 时间复杂度：O(n·L)（L 为文件名长度，计数整体摊还后接近线性）；空间复杂度：O(n)，哈希表存所有名字。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> getFolderNames(vector<string>& names) {  // names：原始文件名列表，原地改写后返回
        unordered_map<string, int> d;  // 哈希表：文件名 → 已用过的最大后缀编号（0/缺省表示未被占用）
        for (auto& name : names) {  // 按顺序处理每个文件名，用引用保证能原地改写
            int k = d[name];  // 取出该名字记录的后缀编号，0 表示第一次出现
            if (k) {  // 非 0 说明重名了，必须加 (k) 后缀
                while (d[name + "(" + to_string(k) + ")"]) {  // 候选后缀名若也被占用，就继续往后试
                    k++;  // 编号递增
                }  // while 循环结束
                d[name] = k;  // 记录该原名的最大编号，下次直接从 k 开始试，避免重复扫描
                name += "(" + to_string(k) + ")";  // 原地给当前文件名加上后缀
            }  // if (k) 分支结束
            d[name] = 1;  // 标记最终文件名已被占用（值为 1 只作占位）
        }  // for 循环结束
        return names;  // 返回保证唯一后的文件名列表
    }  // 方法结束
};  // Solution 类定义结束