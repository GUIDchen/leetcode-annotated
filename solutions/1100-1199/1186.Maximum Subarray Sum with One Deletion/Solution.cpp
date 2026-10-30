// 题目：1186. 删除一次得到子数组最大和（Maximum Subarray Sum with One Deletion）
// 思路：正反各扫一遍求出「以 i 结尾」和「以 i 开头」的最大子数组和，再枚举被删掉的那个位置，把左右两段直接拼接。
// 时间复杂度：O(n)，三次线性扫描；空间复杂度：O(n)，两个长度为 n 的辅助数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumSum(vector<int>& arr) {  // arr：最多允许删除一个元素的数组，返回删除后能得到的最大子数组和
        int n = arr.size();  // 数组长度，后面反复用到，先存下来
        int left[n];  // left[i]：必须包含 arr[i] 的最大子数组和（即以 i 结尾）
        int right[n];  // right[i]：必须包含 arr[i] 的最大子数组和（即以 i 开头）
        for (int i = 0, s = 0; i < n; ++i) {  // 从左往右扫一遍；s 表示「以当前元素结尾」的最大和
            s = max(s, 0) + arr[i];  // 前面的累计和若为负就丢掉，等价于从 arr[i] 重新开始
            left[i] = s;  // 记录下来，之后拼接时直接查表
        }  // 左向扫描结束
        for (int i = n - 1, s = 0; ~i; --i) {  // 从右往左扫一遍；~i 在 i 变成 -1 时值为 0，等价于 i >= 0
            s = max(s, 0) + arr[i];  // 同样的贪心：后缀和为负就丢掉，从 arr[i] 重新开始
            right[i] = s;  // 记录下来，供拼接使用
        }  // 右向扫描结束
        int ans = *max_element(left, left + n);  // 一个元素都不删的情况：直接取 left 的最大值就是普通的「最大子数组和」
        for (int i = 1; i < n - 1; ++i) {  // 枚举被删除的位置 i；首尾删掉等于没删，所以范围是 1 ~ n-2
            ans = max(ans, left[i - 1] + right[i + 1]);  // 删掉 arr[i] 后，以 i-1 结尾的左段与以 i+1 开头的右段直接拼接
        }  // 枚举结束
        return ans;  // 此时 ans 就是最优解
    }  // 方法结束
};  // 类定义结束