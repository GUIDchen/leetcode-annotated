// 题目：1842. 下个由相同数字构成的回文串（Next Palindrome Using Same Digits）🔒
// 思路：回文串由前半段唯一决定，因此只需对前半段求"下一个排列"，成功后再把前半段镜像复制到后半段；前半段已是最大排列则无解，返回空串。
// 时间复杂度：O(n)，next_permutation 单次线性扫描；空间复杂度：O(n)，前半段子串 nums 需要额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string nextPalindrome(string num) {  // num：输入的回文数字串，返回值是下一个更大的回文串
        int n = num.size();  // 原串长度
        string nums = num.substr(0, n / 2);  // 只取前半段，后半段由它镜像决定
        if (!next_permutation(begin(nums), end(nums))) {  // 把前半段原地改成字典序下一个排列
            return "";  // 前半段已是最大排列，不存在更大的同数字回文串
        }
        for (int i = 0; i < n / 2; ++i) {  // 把新的前半段写回原串两端
            num[i] = nums[i];  // 左半部分直接覆盖
            num[n - i - 1] = nums[i];  // 右半部分按下标镜像，保证整体仍是回文
        }
        return num;  // 返回构造好的下一个回文串
    }
};