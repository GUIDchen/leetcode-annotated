// 题目：2593. 标记所有元素后数组的分数（Find Score of an Array After Marking All Elements）
// 思路：把所有元素放进小根堆（按值、下标排序），每次取出最小且未标记的元素累加分数，并标记它与左右邻居，再弹出堆顶已标记的无效元素。
// 时间复杂度：O(n log n)，每个元素入堆出堆各一次；空间复杂度：O(n)，堆与标记数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long findScore(vector<int>& nums) {  // nums 是输入数组，分数可能超过 int 范围所以返回 long long
        int n = nums.size();  // 数组长度
        vector<bool> vis(n);  // vis[i] 表示下标 i 是否已被标记
        using pii = pair<int, int>;  // 堆元素类型：{元素值, 下标}
        priority_queue<pii, vector<pii>, greater<pii>> q;  // 小根堆：值相同时再按下标升序，保证取出的总是最小未标记元素
        for (int i = 0; i < n; ++i) {  // 把所有下标连同元素值一起入堆
            q.emplace(nums[i], i);  // 构造 {nums[i], i} 并压入堆
        }
        long long ans = 0;  // 累计分数
        while (!q.empty()) {  // 堆非空说明还有未标记的元素
            auto [x, i] = q.top();  // 取出当前最小元素的值 x 与下标 i
            q.pop();  // 弹出堆顶
            ans += x;  // 选中的元素计入分数
            vis[i] = true;  // 标记当前下标
            if (i + 1 < n) {  // 右邻居存在时
                vis[i + 1] = true;  // 把它也标记掉
            }
            if (i - 1 >= 0) {  // 左邻居存在时
                vis[i - 1] = true;  // 同样标记掉
            }
            while (!q.empty() && vis[q.top().second]) {  // 堆顶若已被标记就没有使用价值
                q.pop();  // 直接丢弃这些无效元素
            }
        }
        return ans;  // 返回累计得到的分数
    }
};