// 3668. Restore Finishing Order（重排完成顺序）
// 核心思路：先记录每个运动员在 order 中的名次下标，再以该下标为键对 friends 排序，得到完成顺序。
// 复杂度：时间 O(n + m log m)，空间 O(n)；n 为 order 长度，m 为 friends 长度。
class Solution {  // 定义 Solution 类
public:
    vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {  // 恢复完成顺序：返回按 order 名次排好的 friends
        int n = order.size();  // 记录 order 的长度
        vector<int> d(n + 1);  // d[v] 表示运动员 v 在 order 中的下标，即其完成名次
        for (int i = 0; i < n; ++i) {  // 遍历 order，建立运动员到名次下标的映射
            d[order[i]] = i;  // 运动员 order[i] 的名次下标为 i
        }
        sort(friends.begin(), friends.end(), [&](int a, int b) {  // 按各自的名次下标升序排列 friends
            return d[a] < d[b];  // 名次下标更小者排在前面
        });
        return friends;  // 返回按完成顺序重排后的 friends
    }
};
