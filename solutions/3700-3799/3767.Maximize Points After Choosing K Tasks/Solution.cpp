// 3767. 选择 K 个任务的最大总分数 / Maximize Points After Choosing K Tasks
// 核心思路：先假设全部任务都用技术 2，再按“技术1 - 技术2”的差值降序排序，前 k 个强制换成技术 1，其余任务仅在换成技术 1 不亏时才换。
// 复杂度：时间 O(n log n)，空间 O(n)。
class Solution {  // 定义解法类
public:  // 公有方法区
    long long maxPoints(vector<int>& technique1, vector<int>& technique2, int k) {  // 用技术 1 恰好处理 k 个任务，求能获得的最大总分数
        int n = technique1.size();  // 任务数量
        vector<int> idx(n);  // 下标数组，用于按收益差排序
        iota(idx.begin(), idx.end(), 0);  // 填入 0..n-1 的下标

        sort(idx.begin(), idx.end(), [&](int i, int j) {  // 按“技术1 - 技术2”的差值降序排序下标
            return (technique1[j] - technique2[j]) < (technique1[i] - technique2[i]);  // 差值越大，说明换成技术 1 越划算
        });

        long long ans = 0;  // 先假设所有任务都使用技术 2
        for (int x : technique2) {  // 累加技术 2 的总分
            ans += x;  // 累加每个任务的分数
        }

        for (int i = 0; i < k; i++) {  // 前 k 个任务必须使用技术 1
            int index = idx[i];  // 取当前任务下标
            ans -= technique2[index];  // 先减去技术 2 的分数
            ans += technique1[index];  // 再加上技术 1 的分数
        }

        for (int i = k; i < n; i++) {  // 剩余任务只有在技术 1 不劣于技术 2 时才切换
            int index = idx[i];  // 取当前任务下标
            if (technique1[index] >= technique2[index]) {  // 换成技术 1 不会亏
                ans -= technique2[index];  // 减去技术 2 的分数
                ans += technique1[index];  // 加上技术 1 的分数
            }
        }

        return ans;  // 返回最大总分数
    }  // 方法结束
};  // 类结束
