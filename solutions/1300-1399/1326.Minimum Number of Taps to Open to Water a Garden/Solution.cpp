// 题目：1326. 灌溉花园的最少水龙头数目（Minimum Number of Taps to Open to Water a Garden）
// 思路：把每个水龙头看成区间 [i-ranges[i], i+ranges[i]]，预处理 last[l] = 从 l 出发能覆盖到的最远右端点；再按「跳跃游戏 II」的贪心扫描，覆盖断开则无解。
// 时间复杂度：O(n)，两遍线性扫描；空间复杂度：O(n)，last 数组长度为 n+1。
class Solution {  // 题解类
public:  // 对外暴露题解接口
    int minTaps(int n, vector<int>& ranges) {  // n：花园被分成 n 段（0..n 共 n+1 个点）；ranges[i]：第 i 个水龙头的灌溉半径
        vector<int> last(n + 1);  // last[l] 记录所有能覆盖到 l 的水龙头中，能延伸到的最远右端点
        for (int i = 0; i < n + 1; ++i) {  // 枚举每个水龙头，预处理它的覆盖区间
            int l = max(0, i - ranges[i]), r = i + ranges[i];  // 覆盖区间 [l, r]，左端点裁到 0（不能小于花园起点）
            last[l] = max(last[l], r);  // 同一个左端点可能有多个水龙头，只保留能伸得最远的那个
        }  // 预处理结束
        int ans = 0, mx = 0, pre = 0;  // ans：最少水龙头数；mx：当前已选水龙头能覆盖到的最远点；pre：上一段覆盖的右端点
        for (int i = 0; i < n; ++i) {  // 从左往右扫过每一段，判断能否连续覆盖
            mx = max(mx, last[i]);  // 用当前点能开启的水龙头更新最远覆盖
            if (mx <= i) {  // 最远覆盖都没超过当前点，说明这里断了
                return -1;  // 无法浇满整个花园，按题意返回 -1
            }  // 判断结束
            if (pre == i) {  // 走到上一段覆盖的尽头，必须再开水龙头
                ++ans;  // 水龙头数量加一
                pre = mx;  // 新一段的覆盖范围扩展到 mx
            }  // 判断结束
        }  // 扫描结束
        return ans;  // 返回最少水龙头数
    }  // 方法结束
};  // 类定义结束