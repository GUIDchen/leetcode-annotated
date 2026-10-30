// 题目：1013. 将数组分成和相等的三个部分（Partition Array Into Three Parts With Equal Sum）
// 思路：三段和相等必然等于总和的三分之一，所以总和必须能被 3 整除；随后顺序累加，每凑满目标和就切走一段，能切出至少 3 段即满足。
// 时间复杂度：O(n)，先求总和再遍历一次数组；空间复杂度：O(1)，只使用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canThreePartsEqualSum(vector<int>& arr) {  // arr：待划分的整数数组
        int s = accumulate(arr.begin(), arr.end(), 0);  // 求整个数组的总和
        if (s % 3) {  // 总和不能被 3 整除，就不可能三等分
            return false;  // 直接返回 false
        }
        s /= 3;  // 每一段的目标和
        int cnt = 0, t = 0;  // cnt 已经切出的段数，t 当前段正在累加的和
        for (int x : arr) {  // 顺序遍历每个元素
            t += x;  // 把当前元素累加到当前段
            if (t == s) {  // 当前段恰好凑够目标和，就把这一段切走
                t = 0;  // 清零，重新开始累计下一段
                cnt++;  // 段数加一
            }
        }
        return cnt >= 3;  // 能切出 3 段或更多（剩余部分和为 0）就说明可以三等分
    }
};
