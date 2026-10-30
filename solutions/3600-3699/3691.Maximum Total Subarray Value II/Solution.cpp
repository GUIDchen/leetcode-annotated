// 3691. Maximum Total Subarray Value II（3691. 最大子数组总值 II）
// 核心思路：子数组价值 = 区间最大值 - 区间最小值；先用 ST 表做到 O(1) 区间最值查询，再按“固定左端点 l、右端点 r 从 n-1 逐个左移”的方式建大根堆，每次取出当前最大价值并推入 (l, r-1) 的后继，累加前 k 个即为答案。
// 复杂度：时间 O(n log n + k log n)，空间 O(n log n)。
class SparseTableRMQ {  // 定义稀疏表（ST 表）类，支持 O(1) 区间最大值 / 最小值查询
public:  // 公有成员
    int n;  // n 为数组长度
    int maxLog;  // maxLog 为倍增层数上界
    vector<vector<int>> fMax;  // fMax[i][j]：从 i 起长度为 2^j 的区间最大值
    vector<vector<int>> fMin;  // fMin[i][j]：从 i 起长度为 2^j 的区间最小值
    vector<int> lg;  // lg[i] = floor(log2(i))，用于 O(1) 取指数

    SparseTableRMQ(const vector<int>& data) {  // 构造函数：用原数组预处理 ST 表
        n = data.size();  // 记录数组长度
        maxLog = 32 - __builtin_clz(n) + 1;  // 层数取“二进制位数 + 1”，保证 2^j 能覆盖整个区间
        fMax.assign(n, vector<int>(maxLog, 0));  // 分配最大值表
        fMin.assign(n, vector<int>(maxLog, 0));  // 分配最小值表
        lg.assign(n + 1, 0);  // 分配对数表

        for (int i = 2; i <= n; i++) {  // 从小到大递推出 log2 的整数部分
            lg[i] = lg[i >> 1] + 1;  // lg[i] = lg[i/2] + 1
        }  // 循环结束

        for (int i = 0; i < n; i++) {  // 区间长度为 1（j = 0）时的初值就是元素本身
            fMax[i][0] = data[i];  // 长度 1 的区间最大值
            fMin[i][0] = data[i];  // 长度 1 的区间最小值
        }  // 循环结束

        for (int j = 1; j < maxLog; j++) {  // 枚举区间长度 2^j
            for (int i = 0; i <= n - (1 << j); i++) {  // 枚举起点 i，保证区间 i..i+2^j-1 不越界
                fMax[i][j] = max(fMax[i][j - 1], fMax[i + (1 << (j - 1))][j - 1]);  // 左右两个长度 2^(j-1) 的区间取最大合并
                fMin[i][j] = min(fMin[i][j - 1], fMin[i + (1 << (j - 1))][j - 1]);  // 左右两个长度 2^(j-1) 的区间取最小合并
            }  // 起点枚举结束
        }  // 长度枚举结束
    }  // 构造函数结束

    int queryMax(int l, int r) {  // 查询闭区间 [l, r] 的最大值
        int k = lg[r - l + 1];  // 取不超过区间长度的最大 2 的幂的指数 k
        return max(fMax[l][k], fMax[r - (1 << k) + 1][k]);  // 用两段长度 2^k 的区间覆盖 [l, r] 取最大（允许重叠）
    }  // 查询函数结束

    int queryMin(int l, int r) {  // 查询闭区间 [l, r] 的最小值
        int k = lg[r - l + 1];  // 同上，求指数 k
        return min(fMin[l][k], fMin[r - (1 << k) + 1][k]);  // 用两段长度 2^k 的区间覆盖 [l, r] 取最小（允许重叠）
    }  // 查询函数结束
};  // ST 表类定义结束

class Solution {  // 定义题解类
public:  // 公有接口
    long long maxTotalValue(vector<int>& nums, int k) {  // 主函数：从所有子数组中取价值最大的 k 个（每个子数组至多选一次），返回价值之和
        int n = nums.size();  // n 为数组长度
        SparseTableRMQ st(nums);  // 预处理 ST 表，用于 O(1) 求区间最值
        auto cmp = [](const tuple<long long, int, int>& a, const tuple<long long, int, int>& b) {  // 声明比较器：按价值从大到小排列，构成大根堆
            return get<0>(a) < get<0>(b);  // 价值大的排在堆顶
        };  // 比较器结束
        priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, decltype(cmp)> pq(cmp);  // 大根堆，元素为（价值, 左端点, 右端点）

        for (int l = 0; l < n; l++) {  // 对每个左端点 l 初始化右端点为 n-1
            long long val = st.queryMax(l, n - 1) - st.queryMin(l, n - 1);  // 价值 = 区间最大值 - 区间最小值
            pq.push({val, l, n - 1});  // 把（价值, l, n-1）入堆
        }  // 循环结束

        long long ans = 0;  // ans 累加被选中的 k 个子数组价值
        for (int i = 0; i < k; i++) {  // 一共取 k 个子数组
            auto curr = pq.top();  // 取出堆顶，即当前价值最大的子数组
            pq.pop();  // 弹出堆顶
            long long val = get<0>(curr);  // 解包价值
            int l = get<1>(curr);  // 解包左端点
            int r = get<2>(curr);  // 解包右端点
            ans += val;  // 累加该子数组的价值
            if (r > l) {  // 右端点还能继续左移，产生同左端点的后继候选
                long long nextVal = st.queryMax(l, r - 1) - st.queryMin(l, r - 1);  // 后继价值：左端点不变、右端点减一
                pq.push({nextVal, l, r - 1});  // 把后继入堆
            }  // if 分支结束
        }  // 循环结束
        return ans;  // 返回前 k 大子数组价值之和
    }  // 主函数结束
};  // 类定义结束