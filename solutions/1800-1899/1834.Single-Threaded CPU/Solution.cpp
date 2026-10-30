// 题目：1834. 单线程 CPU（Single-Threaded CPU）
// 思路：给每个任务补上原始下标后按入队时间排序，用最小堆按 (耗时, 下标) 取出当前可执行的最优先任务；堆空时把时间跳到下一任务的入队时刻，逐次模拟即可。
// 时间复杂度：O(n log n)，排序 O(n log n) 且每个任务进出堆各一次；空间复杂度：O(n)，堆与答案数组最坏各存 n 项。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getOrder(vector<vector<int>>& tasks) {  // tasks 每行为 [入队时间, 处理耗时]，返回任务原始下标的执行顺序
        int n = 0;  // n 既是任务总数，也用作追加下标时的自增计数器
        for (auto& task : tasks) task.push_back(n++);  // 给每个任务追加原始下标，排序后仍能找回它在输入中的位置
        sort(tasks.begin(), tasks.end());  // 按 [入队时间, 耗时, 原始下标] 的字典序升序排序
        using pii = pair<int, int>;  // 类型别名 pii 即 pair<int, int>，堆元素为 (耗时, 原始下标)
        priority_queue<pii, vector<pii>, greater<pii>> q;  // 小根堆：耗时小的先出堆，耗时相同则下标小的先出堆
        int i = 0;  // i 指向下一个尚未入堆的任务
        long long t = 0;  // 当前时间 t 可能超出 int 范围，故用 long long
        vector<int> ans;  // 保存任务执行顺序（里面存的是原始下标）
        while (!q.empty() || i < n) {  // 堆里还有待执行任务，或还有任务没入堆，就继续模拟
            if (q.empty()) t = max(t, (long long) tasks[i][0]);  // 堆空意味着 CPU 空闲，时间直接跳到下一任务的最早入队时刻
            while (i < n && tasks[i][0] <= t) {  // 把入队时间已到的任务全部压入堆，它们从此开始排队等待
                q.push({tasks[i][1], tasks[i][2]});  // 入堆 (耗时, 原始下标)，入队时间已不再需要
                ++i;  // 该任务已入堆，指针后移
            }  // 可执行任务已全部入堆
            auto [pt, j] = q.top();  // 取出最优任务，结构化绑定解构为耗时 pt 与原始下标 j
            q.pop();  // 该任务出堆，即将占用 CPU
            ans.push_back(j);  // 把原始下标追加到答案
            t += pt;  // 时间推进 pt，表示 CPU 忙完这个任务
        }  // 模拟结束
        return ans;  // 所有任务都执行完，返回执行顺序
    }  // 方法结束
};  // 类定义结束