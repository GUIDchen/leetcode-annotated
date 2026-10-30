// 题目：347. 前 K 个高频元素（Top K Frequent Elements）
// 思路：先用哈希表统计每个元素的出现次数，再用「以频率为关键字的小根堆」维护频率最高的 k 个元素，堆顶始终是这 k 个里频率最低的。
// 时间复杂度：O(n log k)，每个不同元素最多进出堆一次；空间复杂度：O(n)，哈希表加大小为 k 的堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> topKFrequent(vector<int>& nums, int k) {  // nums：输入数组；k：要求返回的高频元素个数；返回任意顺序的前 k 个高频元素
        unordered_map<int, int> cnt;  // 哈希表：键是元素值，值是它出现的次数
        using pii = pair<int, int>;  // 给 pair<int, int> 起别名 pii，后面声明优先队列时更简洁
        for (int x : nums) {  // 遍历数组，逐个累计出现次数
            ++cnt[x];  // 当前元素计数加一（unordered_map 对不存在的键会自动初始化为 0）
        }  // 统计阶段结束
        priority_queue<pii, vector<pii>, greater<pii>> pq;  // 小根堆：元素是 (频率, 数值)，greater 让频率最小的浮到堆顶，便于超员时淘汰
        for (auto& [x, c] : cnt) {  // 结构化绑定遍历哈希表，x 是元素值、c 是它的频率
            pq.push({c, x});  // 把 (频率, 数值) 压入堆中
            if (pq.size() > k) {  // 堆内元素超过 k 个，需要淘汰频率最低的那个
                pq.pop();  // 弹出堆顶，即当前 k+1 个里频率最小的元素
            }  // if 结束
        }  // 遍历结束
        vector<int> ans;  // 准备存放答案的数组
        while (!pq.empty()) {  // 堆中剩下正是频率最高的 k 个元素
            ans.push_back(pq.top().second);  // 取堆顶 pair 的 second 部分，也就是元素值
            pq.pop();  // 弹出堆顶，继续取下一个
        }  // while 结束
        return ans;  // 返回结果（题目不要求顺序）
    }  // 方法体结束
};  // 类定义结束
