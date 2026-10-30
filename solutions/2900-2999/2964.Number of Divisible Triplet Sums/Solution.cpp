// 题目：2964. 可被整除的三元组数量（Number of Divisible Triplet Sums）
// 思路：枚举三元组的中间下标 j，用哈希表记录 j 左侧所有数字 mod d 的余数个数，对每个右侧下标 k 直接查补余数累加答案。
// 时间复杂度：O(n^2)，枚举 j 与 k 两层循环；空间复杂度：O(min(n, d))，哈希表最多保存 d 种不同的余数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int divisibleTripletCount(vector<int>& nums, int d) {  // nums：输入数组；d：除数；返回下标 i<j<k 且三数之和能被 d 整除的三元组个数
        unordered_map<int, int> cnt;  // 哈希表：键是数字 mod d 的余数，值是下标小于当前 j 的这类数字的个数
        int ans = 0, n = nums.size();  // ans 统计答案；n 缓存数组长度
        for (int j = 0; j < n; ++j) {  // 枚举三元组的中间下标 j
            for (int k = j + 1; k < n; ++k) {  // 枚举 j 右侧的下标 k，这样 i<j<k 的大小顺序天然满足
                int x = (d - (nums[j] + nums[k]) % d) % d;  // 要让 (nums[i]+nums[j]+nums[k]) % d == 0，nums[i] % d 必须等于这个补余数（再取一次模处理余数为 0 的情况）
                ans += cnt[x];  // 之前扫过的元素都在 j 左侧，可直接充当 i，把满足该余数的个数累加
            }  // k 循环结束
            cnt[nums[j] % d]++;  // 处理完所有 k 之后，把 j 也加入哈希表，供后面更大的 j 当作左侧下标 i 使用
        }  // j 循环结束
        return ans;  // 返回三元组总数
    }  // 方法结束
};  // 类定义结束