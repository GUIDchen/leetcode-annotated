// 题目：1550. 存在连续三个奇数的数组（Three Consecutive Odds）
// 思路：一次遍历，用计数器记录当前连续奇数的个数，遇到偶数就清零，计数到 3 立刻返回 true。
// 时间复杂度：O(n)，最多扫描一遍数组；空间复杂度：O(1)，只用一个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool threeConsecutiveOdds(vector<int>& arr) {  // arr：待检查的整数数组
        int cnt = 0;  // cnt：当前已经连续遇到多少个奇数
        for (int x : arr) {  // 从头到尾逐个遍历数组元素
            if (x & 1) {  // 用最低位判断奇偶：为 1 说明是奇数
                if (++cnt == 3) {  // 奇数计数先自增，正好到 3 说明已经满足条件
                    return true;  // 找到连续三个奇数，立即返回 true
                }
            } else {  // 当前元素是偶数
                cnt = 0;  // 连续奇数被偶数打断，计数器清零重新开始
            }
        }
        return false;  // 遍历结束仍未出现连续三个奇数，返回 false
    }
};
