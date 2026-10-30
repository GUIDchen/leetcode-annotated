// 题目：822. 翻转卡片游戏（Card Flipping Game）
// 思路：正反面数字相同的卡片无论怎么翻都会露出这个数，所以它永远不能作为答案，先收集进「坏数字」集合；再在所有卡片的正反面里找不属于该集合的最小值。
// 时间复杂度：O(n)，只需线性扫描；空间复杂度：O(n)，坏数字集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int flipgame(vector<int>& fronts, vector<int>& backs) {  // fronts/backs：每张卡片的正面与反面
        unordered_set<int> s;  // 记录「正反面数字相同」的数字：它们无论怎么翻都会露出来，永远不能作为答案
        int n = fronts.size();  // 卡片数量
        for (int i = 0; i < n; ++i) {  // 逐张检查
            if (fronts[i] == backs[i]) {  // 正反面数字相同
                s.insert(fronts[i]);  // 该数字无法通过翻面避开，记为坏数字
            }  // if 结束
        }  // 第一轮收集结束
        int ans = 9999;  // 用 9999 作哨兵（数字范围是 1..2000）
        for (int& v : fronts) {  // 遍历所有正面数字
            if (!s.count(v)) {  // 不是坏数字就可以作为答案
                ans = min(ans, v);  // 更新最小值
            }  // if 结束
        }  // 正面遍历结束
        for (int& v : backs) {  // 再遍历所有反面数字（翻面后可能露出的数字）
            if (!s.count(v)) {  // 不是坏数字就可以作为答案
                ans = min(ans, v);  // 更新最小值
            }  // if 结束
        }  // 反面遍历结束
        return ans % 9999;  // 没找到时 ans 仍为 9999，取模后返回 0；否则返回最小值
    }  // flipgame 方法结束
};  // Solution 类结束