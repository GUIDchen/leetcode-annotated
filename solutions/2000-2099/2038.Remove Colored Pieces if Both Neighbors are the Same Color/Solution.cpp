// 题目：2038. 如果相邻两个颜色均相同则删除当前颜色（Remove Colored Pieces if Both Neighbors are the Same Color）
// 思路：按同色段统计，长度 L 的段该颜色玩家最多可删 L-2 次；求出双方各自可删次数后比较大小即可。
// 时间复杂度：O(n)，每个字符最多被 j 指针扫过一遍；空间复杂度：O(1)，只用常数个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool winnerOfGame(string colors) {  // colors：仅由 'A'、'B' 组成的颜色串
        int n = colors.size();  // n：字符串长度，作为循环边界
        int a = 0, b = 0;  // a 记 Alice（'A'）的可删次数，b 记 Bob（'B'）的可删次数
        for (int i = 0, j = 0; i < n; i = j) {  // 外层循环按同色段跳跃：i 是当前段起点，j 复用为段尾指针
            while (j < n && colors[j] == colors[i]) {  // j 从段起点向后扩张，直到遇见不同颜色或越界
                ++j;  // 颜色仍相同，继续右移
            }  // 此时 [i, j) 是一段完整的同色段
            int m = j - i - 2;  // 段长 L = j - i，最多可删 L-2 次；段长不足 3 时 m 不为正
            if (m > 0) {  // 只有长度至少为 3 的段才有可删机会
                if (colors[i] == 'A') {  // 这段颜色属于 Alice
                    a += m;  // 累加 Alice 的可删次数
                } else {  // 否则这段颜色属于 Bob
                    b += m;  // 累加 Bob 的可删次数
                }
            }
        }  // 处理完一段后 i 直接跳到 j，避免重复扫描同一段
        return a > b;  // 两人都每次只删一个，Alice 可删次数严格多于 Bob 才必胜
    }
};