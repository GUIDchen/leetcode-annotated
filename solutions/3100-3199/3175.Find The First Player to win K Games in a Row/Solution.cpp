// 题目：3175. 找到连续赢 K 场比赛的第一位玩家（Find The First Player to win K Games in a Row）
// 思路：比赛按队列顺序进行，i 是当前擂主，j 依次是挑战者；挑战者更强就换擂主并把连胜重置为 1，否则擂主连胜数加一。全局最强者当上擂主后不会再输，所以最多比较 n-1 场，把 k 截断为 min(k, n-1) 后若中途没 break，最终 i 就是全局最强者的下标。
// 时间复杂度：O(n)，数组最多扫描一遍；空间复杂度：O(1)，只用常数个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findWinningPlayer(vector<int>& skills, int k) {  // skills 是每个玩家的实力值（互不相同），k 是需要的连续获胜场数，返回获胜玩家的下标
        int n = skills.size();  // 玩家总数
        k = min(k, n - 1);  // 全局最强者当上擂主后不会再输，因此 k 超过 n-1 时结果与 k=n-1 相同，可以截断
        int i = 0, cnt = 0;  // i 是当前擂主下标，cnt 是擂主已经连续赢下的场数
        for (int j = 1; j < n; ++j) {  // 挑战者从下标 1 开始依次上场
            if (skills[i] < skills[j]) {  // 挑战者实力更强，说明擂主输掉这一场
                i = j;  // 擂主换成挑战者，i 始终指向当前擂主
                cnt = 1;  // 新擂主刚赢下这一场，连胜数从 1 重新开始
            } else {  // 否则擂主守住，继续累加连胜数
                ++cnt;  // 擂主连胜场数加一
            }
            if (cnt == k) {  // 已经连续赢了 k 场，i 就是答案
                break;  // 提前结束扫描
            }
        }
        return i;  // 返回第一个连续赢 k 场的玩家下标（未提前结束时即全局最强者）
    }
};