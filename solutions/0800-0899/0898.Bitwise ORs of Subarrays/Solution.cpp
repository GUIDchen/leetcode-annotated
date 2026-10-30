// 题目：898. 子数组按位或操作（Bitwise ORs of Subarrays）
// 核心思路：集合 s 保存「以当前元素结尾」的所有子数组或值，逐元素滚动更新并累计到答案集合 ans。
// 时间复杂度：O(n log C)，每个位置的不同或值至多 O(log C) 种；空间复杂度：O(n log C) 保存全部结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int subarrayBitwiseORs(vector<int>& arr) {  // arr：输入数组
        unordered_set<int> ans;  // 存放所有子数组出现过的或值（去重）
        unordered_set<int> s;  // 存放「以当前元素结尾」的所有子数组或值
        for (int x : arr) {  // 从左到右逐个处理元素
            unordered_set<int> t;  // 存放「以 x 结尾」的新一轮或值
            for (int y : s) {  // 枚举上一轮的所有或值
                t.insert(x | y);  // 在旧子数组后面接上 x，得到新的或值
            }  // 只含 x 本身的子数组
            t.insert(x);  // 这一轮的或值全部并入答案集合
            ans.insert(t.begin(), t.end());  // 用 t 替换 s，避免拷贝
            s = move(t);  // 不同或值的个数即为答案
        }
        return ans.size();
    }
};