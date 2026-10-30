// 题目：4049. 统计等间距出现整数数目 II（Count Values With Equally Spaced Occurrences II）
// 思路：哈希表把「整数 → 出现下标列表」分组，再逐组检查：出现次数不足 3 次直接跳过，否则以第一段间隔为基准，验证所有相邻下标之差是否都相等，全部相等才算等间距出现。
// 复杂度：时间复杂度 O(n)，n 为数组长度（每个下标只被检查常数次）；空间复杂度 O(n)，哈希表存放所有下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countSpecialIntegers(vector<int>& nums) {  // nums：输入数组；返回所有出现位置等间距（至少 3 次）的不同整数个数
        unordered_map<int, vector<int>> g;  // g[x]：整数 x 出现的所有下标
        for (int i = 0; i < nums.size(); i++) {  // 遍历数组，收集每个值的出现位置
            g[nums[i]].push_back(i);  // 把下标 i 追加到该值的列表末尾
        }  // 建表循环结束

        int ans = 0;  // 满足条件的整数个数
        for (auto& [x, pos] : g) {  // 遍历每个值及其位置列表
            if (pos.size() < 3) {  // 出现次数不足 3 次，不可能等间距
                continue;  // 直接跳过这一组
            }  // 跳过分支结束

            int d = pos[1] - pos[0];  // 以第一段间隔作为基准间隔
            bool ok = true;  // 先假设所有间隔都相等
            for (int i = 1; i < pos.size(); i++) {  // 逐段检查相邻下标之差
                if (pos[i] - pos[i - 1] != d) {  // 有一段间隔与基准不同
                    ok = false;  // 标记为不满足
                    break;  // 提前结束检查
                }  // 判断分支结束
            }  // 间隔检查循环结束

            if (ok) {  // 所有间隔都相等
                ans++;  // 计数加一
            }  // 判断分支结束
        }  // 分组遍历结束
        return ans;  // 返回满足条件的整数个数
    }  // 方法结束
};  // 题解类结束