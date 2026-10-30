// 题目：786. 第 K 个最小的质数分数（K-th Smallest Prime Fraction）
// 思路：把 n-1 个「每个分母下的最小分数 arr[0]/arr[j]」放进小根堆；弹出 k-1 次，每次把同分母的下一个分子补进堆。
// 时间复杂度：O((n + k) log n)，每次堆操作 O(log n)；空间复杂度：O(n)，堆中最多 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {  // arr 是升序质数数组，k 是目标名次（从 1 开始）
        using pii = pair<int, int>;  // 用二元组 (分子下标, 分母下标) 代表一个分数
        int n = arr.size();  // 数组长度
        auto cmp = [&](const pii& a, const pii& b) {  // 小根堆比较器：交叉相乘比较，避免浮点误差
            return arr[a.first] * arr[b.second] > arr[b.first] * arr[a.second];  // a 代表的分数更大时返回 true，于是堆顶始终是当前最小分数
        };  // 比较器 lambda 定义结束
        priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);  // 以 cmp 为比较器声明小根堆（decltype(cmp) 取得 lambda 类型）
        for (int i = 1; i < n; ++i) {  // 分母下标从 1 开始，因为分子必须严格小于分母
            pq.push({0, i});  // 每个分母下最小的分数是 arr[0]/arr[j]，先把这 n-1 个起点全部入堆
        }  // 入堆循环结束
        for (int i = 1; i < k; ++i) {  // 只需弹出前 k-1 个最小值，此时堆顶就是第 k 小
            pii f = pq.top();  // 取出当前全堆最小分数
            pq.pop();  // 把它弹出堆
            if (f.first + 1 < f.second) {  // 同一分母下还有下一个分数（分子还必须小于分母）
                pq.push({f.first + 1, f.second});  // 把该分母的下一个分数补进堆，保证候选不遗漏
            }  // 条件分支结束
        }  // 弹出循环结束
        return {arr[pq.top().first], arr[pq.top().second]};  // 堆顶即第 k 小分数，返回它的分子值与分母值
    }  // 方法结束
};  // 题解类结束