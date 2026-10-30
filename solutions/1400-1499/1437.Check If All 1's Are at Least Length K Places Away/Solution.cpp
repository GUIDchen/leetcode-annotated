// 题目：1437. 是否所有 1 都至少相隔 k 个元素（Check If All 1's Are at Least Length K Places Away）
// 思路：一次遍历记录上一个 1 的下标，遇到新的 1 就地算出两者之间夹着多少个元素，与 k 比较。
// 时间复杂度：O(n)，n 为数组长度；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool kLengthApart(vector<int>& nums, int k) {  // nums 是 0/1 数组，k 是要求的最小间隔元素个数
        int j = -(k + 1);  // j 是上一个 1 的下标；初始取 -(k+1)，使第一个 1 与它的距离天然满足要求
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右扫描每个位置
            if (nums[i] == 1) {  // 遇到一个 1，就要检查它和上一个 1 的间距
                if (i - j - 1 < k) {  // 两者之间夹着的元素个数 i-j-1 小于 k，不合要求
                    return false;  // 立即返回假，无需继续扫描
                }
                j = i;  // 记下这个 1 的位置，供下一个 1 比较
            }
        }
        return true;  // 所有 1 都检查完毕，没有违规
    }
};