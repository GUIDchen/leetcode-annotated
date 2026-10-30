// 题目：2833. 距离原点最远的点（Furthest Point From Origin）
// 思路：统计 'L'、'R'、'_' 三种字符的个数。先按 L 与 R 的差值得到固定位移，'_' 每个都可以任选方向，全部用来加大距离，因此答案就是 |cntL - cntR| + cnt_。
// 时间复杂度：O(n)，三次遍历字符串统计字符（n 为串长）；空间复杂度：O(1)，只用了常数个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int furthestDistanceFromOrigin(string moves) {  // moves：由 'L'、'R'、'_' 组成的移动序列
        auto cnt = [&](char c) {  // 定义一个按字符统计次数的 lambda，捕获 moves
            return count(moves.begin(), moves.end(), c);  // 用标准库 count 统计字符 c 在串中出现的次数
        };  // lambda 定义结束
        return abs(cnt('L') - cnt('R')) + cnt('_');  // 固定位移的绝对值加上所有 '_' 都朝同侧带来的额外位移
    }
};