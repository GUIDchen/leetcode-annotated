// 3597. 分割字符串（Partition String）
// 核心思路：从左到右贪心累积字符，一旦当前子串从未出现过就把它作为新的一段切入答案，保证各段互不相同。
// 复杂度：时间 O(n^2)（字符串哈希与比较），空间 O(n^2)（保存所有子串）。
class Solution {  // 主解类
public:  // 对外接口
    vector<string> partitionString(string s) {  // 把 s 分割成若干互不相同的最短子串
        unordered_set<string> vis;  // 哈希集合：记录已经出现过的子串
        vector<string> ans;  // 保存分割结果
        string t = "";  // 当前正在累积的子串
        for (char c : s) {  // 从左到右逐字符扫描
            t += c;  // 把当前字符拼到累积串末尾
            if (!vis.contains(t)) {  // 拼出了此前没见过的新子串
                vis.insert(t);  // 记录该子串
                ans.push_back(t);  // 作为一个新段加入答案
                t = "";  // 清空累积串，开始下一段
            }  // if 结束
        }  // 循环结束
        return ans;  // 返回最终的分割结果
    }  // partitionString 结束
};  // 类定义结束