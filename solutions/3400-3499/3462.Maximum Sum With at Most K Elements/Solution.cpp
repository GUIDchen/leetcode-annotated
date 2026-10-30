// 3462. 提取至多 K 个元素的最大总和 / Maximum Sum With at Most K Elements
// 核心思路：每行升序排序后只取不超过 limits[i] 个最大值，用小顶堆维护全局最大的至多 k 个元素，最后求和。
// 复杂度：时间 O(S log L + S log k)，空间 O(k + L)，S 为各行取数总量、L 为单行长度。
class Solution {  // 定义题解类
public:  // 公有方法
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {  // 返回至多选 k 个元素能得到的最大总和
        priority_queue<int, vector<int>, greater<int>> pq;  // 小顶堆，保留当前全局最大的至多 k 个元素
        int n = grid.size();  // 矩阵行数

        for (int i = 0; i < n; ++i) {  // 逐行处理
            vector<int> nums = grid[i];  // 拷贝当前行，避免修改原矩阵
            int limit = limits[i];  // 该行最多可选出的元素个数
            ranges::sort(nums);  // 升序排序，末尾即为最大值

            for (int j = 0; j < limit; ++j) {  // 取该行前 limit 大的元素
                pq.push(nums[nums.size() - j - 1]);  // 压入该行第 j+1 大的元素
                if (pq.size() > k) {  // 堆内元素超过 k 个
                    pq.pop();  // 弹出最小值，保证堆里始终是最大的 k 个
                }  // 结束超量弹出分支
            }  // 结束本行取数循环
        }  // 结束逐行处理循环

        long long ans = 0;  // 答案累加器
        while (!pq.empty()) {  // 遍历堆中剩余的至多 k 个元素
            ans += pq.top();  // 累加当前最小值
            pq.pop();  // 弹出该元素
        }  // 结束求和循环

        return ans;  // 返回最大总和
    }  // 结束方法
};  // 结束类定义
