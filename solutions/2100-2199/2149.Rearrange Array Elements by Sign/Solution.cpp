// 题目：2149. 按符号重排数组（Rearrange Array Elements by Sign）
// 思路：新建答案数组，用两个指针分别指向下一个待填的偶数位（放正数）和奇数位（放负数），一次遍历即可保持组内相对顺序。
// 时间复杂度：O(n)，只需遍历一次；空间复杂度：O(n)，需要长度为 n 的答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> rearrangeArray(vector<int>& nums) {  // nums：正负数量相等、正负交替重排前的数组
        vector<int> ans(nums.size());  // 预先分配与输入等长的答案数组
        int i = 0, j = 1;  // i：下一个放正数的偶数下标；j：下一个放负数的奇数下标
        for (int x : nums) {  // 按原顺序遍历每个元素
            if (x > 0) {  // 正数走偶数位
                ans[i] = x;  // 把正数写入当前偶数位
                i += 2;  // 偶数位指针后移两位
            } else {  // 负数走奇数位
                ans[j] = x;  // 把负数写入当前奇数位
                j += 2;  // 奇数位指针后移两位
            }
        }
        return ans;  // 返回正负交替排列好的数组
    }
};  // 类定义结束