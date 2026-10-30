// 题目：1691. 堆叠长方体的最大高度（Maximum Height by Stacking Cuboids）
// 思路：先把每个长方体的三边升序排列（最小的两条作底面、最大的作高），整体排序后用最长上升子序列式 DP 求最大堆叠高度。
// 时间复杂度：O(n^2) 的 DP 转移（排序 O(n log n)）；空间复杂度：O(n) 的 DP 数组 f。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxHeight(vector<vector<int>>& cuboids) {  // cuboids[i] 是第 i 个长方体的三个维度
        for (auto& c : cuboids) {  // 逐个体处理
            sort(c.begin(), c.end());  // 三边升序排列：最小两条作底面，最大一条作高
        }  // 排序循环结束
        sort(cuboids.begin(), cuboids.end());  // 整体字典序排序，保证可能垫在下面的长方体排在前面
        int n = cuboids.size();  // 长方体个数
        vector<int> f(n);  // f[i]：以第 i 个长方体作堆顶时的最大总高度
        for (int i = 0; i < n; ++i) {  // 依次把第 i 个长方体当作堆顶
            for (int j = 0; j < i; ++j) {  // 枚举可能垫在它下面的第 j 个长方体
                if (cuboids[j][1] <= cuboids[i][1] && cuboids[j][2] <= cuboids[i][2]) {  // 两个底面维度都不超过上方长方体，才能合法堆叠
                    f[i] = max(f[i], f[j]);  // 继承下面那一摞的最大高度
                }  // 堆叠条件判断结束
            }  // 枚举 j 的循环结束
            f[i] += cuboids[i][2];  // 加上第 i 个长方体自身的高度
        }  // 枚举堆顶 i 的循环结束
        return *max_element(f.begin(), f.end());  // 所有堆法中的最大高度
    }  // 方法结束
};  // 类结束