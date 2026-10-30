// 题目：2379. 得到 K 个黑块的最少涂色次数（Minimum Recolors to Get K Consecutive Black Blocks）
// 思路：定长滑窗，统计每个长度为 k 的窗口内 'W' 的个数；把窗口内的 'W' 全部涂黑即可得到连续 k 个黑块，所以取所有窗口中的最小 'W' 数。
// 时间复杂度：O(n)，每个字符只进出窗口一次；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumRecolors(string blocks, int k) {  // blocks 为 'B'/'W' 字符串，k 为需要的连续黑块长度
        int cnt = count(blocks.begin(), blocks.begin() + k, 'W');  // 统计首个窗口 [begin, begin + k) 内 'W' 的个数，即需要涂色的次数
        int ans = cnt;  // 先把首个窗口的结果作为当前最优答案
        for (int i = k; i < blocks.size(); ++i) {  // 窗口右端从 k 开始逐格右移
            cnt += blocks[i] == 'W';  // 右端新元素若为 'W'，需要涂色的次数加一
            cnt -= blocks[i - k] == 'W';  // 左端滑出窗口的元素若为 'W'，需要涂色的次数减一
            ans = min(ans, cnt);  // 用当前窗口的涂色次数更新最小值
        }  // 滑窗遍历结束
        return ans;  // 返回最小的涂色次数
    }  // minimumRecolors 方法结束
};  // Solution 类结束