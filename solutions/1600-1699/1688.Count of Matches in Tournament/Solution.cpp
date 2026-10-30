// 题目：1688. 比赛中的配对次数（Count of Matches in Tournament）
// 思路：每场比赛恰好淘汰一支队伍，n 支队伍决出唯一冠军必然要淘汰 n-1 支，所以答案就是 n-1。
// 时间复杂度：O(1)，一次减法；空间复杂度：O(1)，不使用额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfMatches(int n) {  // n：参赛队伍数
        return n - 1;  // 淘汰 n-1 支队伍即 n-1 场比赛
    }  // 方法结束
};  // 类结束