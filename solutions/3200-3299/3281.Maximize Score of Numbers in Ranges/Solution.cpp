// 3281. 范围内整数的最大得分（Maximize Score of Numbers in Ranges）
// 核心思路：二分答案。对候选得分 x，贪心地在每个区间 [st, st+d] 中取不小于「上一个已选值 + x」的最小值；若某个区间放不下说明 x 过大，据此二分最大可行 x。
// 复杂度：时间 O(n log n + n log U)，空间 O(1)，U 为数值范围

class Solution {  // 定义题解类
public:  // 公开接口
    int maxPossibleScore(vector<int>& start, int d) {  // 返回能够取到的最大得分
        ranges::sort(start);  // 按区间左端点升序排序，保证贪心自左向右进行
        auto check = [&](int mi) -> bool {  // 判定：是否存在给每个区间选一个数、使相邻已选值之差都不小于 mi 的方案
            long long last = LLONG_MIN;  // 上一个选中的数，初始为负无穷
            for (int st : start) {  // 按区间从左到右贪心
                if (last + mi > st + d) {  // 区间内找不到不小于 last + mi 的数，说明 mi 太大
                    return false;  // 该得分不可行
                }  // 结束可行性判断
                last = max((long long) st, last + mi);  // 在 [st, st + d] 中取满足间隔要求的最小值，给后面留出更多空间
            }  // 结束贪心
            return true;  // 所有区间都能放下，该得分可行
        };  // lambda 定义结束
        int l = 0, r = start.back() + d - start[0];  // 二分区间：下界 0，上界取可能的最大跨度
        while (l < r) {  // 二分寻找最大可行得分
            int mid = l + (r - l + 1) / 2;  // 向上取整的中点，避免只剩两个元素时死循环
            if (check(mid)) {  // mid 可行
                l = mid;  // 答案至少是 mid，向右收缩
            } else {  // mid 不可行
                r = mid - 1;  // 答案小于 mid，向左收缩
            }  // 结束二分分支
        }  // 结束二分
        return l;  // 返回最大可行得分
    }  // 方法结束
};  // 类定义结束
