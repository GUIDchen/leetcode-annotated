// 题目：1552. 两球之间的磁力（Magnetic Force Between Two Balls）
// 思路：先排序，再对"最小磁力"二分答案：给定间距 f 时贪心统计最多能放几个球，能放够 m 个就说明 f 可行，向右收缩。
// 时间复杂度：O(n log n + n log(maxPos))（排序 + 每次 check 线性扫描）；空间复杂度：O(1)（原地排序，只用常数变量）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxDistance(vector<int>& position, int m) {  // position：篮子位置；m：需要放入的球数
        ranges::sort(position);  // C++20 的 ranges 版排序，把位置升序排列，便于从左往右贪心放球
        int l = 1, r = position.back();  // 二分答案的区间：最小磁力至少为 1，最大不超过两端点距离
        auto count = [&](int f) {  // 定义 lambda：计算在"相邻球间距 >= f"的约束下最多能放几个球
            int prev = position[0];  // 贪心地把第一个球放在最左边的位置
            int cnt = 1;  // 已经放置的球数，初始放入第一个球
            for (int& curr : position) {  // 从左到右扫描每个位置（引用遍历避免复制）
                if (curr - prev >= f) {  // 与上一个球的距离达到 f，说明这个位置可以再放一个球
                    prev = curr;  // 更新上一个球的位置
                    cnt++;  // 放置球数加一
                }
            }
            return cnt;  // 返回该间距下最多能放的球数
        };
        while (l < r) {  // 二分查找最大的可行间距（区间为闭区间）
            int mid = (l + r + 1) >> 1;  // 取上中位数，避免 l == r-1 时死循环
            if (count(mid) >= m) {  // 该间距下能放下至少 m 个球，说明 mid 可行，答案在右侧
                l = mid;  // 保留可行解，把左边界抬到 mid
            } else {  // 该间距太苛刻，放不下 m 个球
                r = mid - 1;  // 缩小右边界
            }
        }
        return l;  // 循环结束时 l 就是最大的可行最小磁力
    }
};
