// 题目：3524. 求出数组的 X 值 I（Find X Value of Array I）
// 思路：按右端点做余数 DP。f[r] 表示以当前元素结尾、乘积模 k 余 r 的子数组个数；每步让旧分布整体乘上 x，再加上单元素段，并累加进答案。
// 时间复杂度：O(n·k)，每个元素只处理 k 个余数；空间复杂度：O(k)，只保留上一轮的分布。
class Solution {  // LeetCode 约定的题解类
public:  // 判题器只调用 public 区的方法
    vector<long long> resultArray(vector<int>& nums, int k) {  // nums 为输入数组，k 为模数，返回长度 k 的答案数组
        vector<long long> ans(k);  // ans[r] 统计乘积模 k 余 r 的所有子数组个数
        vector<long long> f(k);  // f[r]：以「上一个元素」结尾、乘积模 k 余 r 的子数组个数
        for (int x : nums) {  // 依次把每个元素当作子数组的右端点
            vector<long long> g(k);  // g 是本轮（以 x 结尾）的余数分布
            for (int r = 0; r < k; ++r) {  // 枚举上一轮已有的每个余数
                g[1LL * r * x % k] += f[r];  // 旧子数组再接上 x，余数变为 r*x%k，个数照搬
            }  // 继承旧子数组的部分结束
            g[x % k] += 1;  // 再加上只含 x 本身的单元素子数组
            for (int r = 0; r < k; ++r) {  // 把本轮分布累加进总答案
                ans[r] += g[r];  // 以 x 结尾的每个子数组都计入对应余数
            }  // 累加结束
            f.swap(g);  // 滚动数组：本轮分布成为下一轮的「上一轮分布」
        }  // 右端点遍历结束
        return ans;  // 返回每个余数对应的子数组个数
    }  // 方法结束
};  // 类定义结束
