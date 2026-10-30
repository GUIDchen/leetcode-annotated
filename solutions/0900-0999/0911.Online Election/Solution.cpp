// 题目：911. 在线选举（Online Election）
// 核心思路：构造时按时间顺序扫一遍投票记录，用计数数组维护当前票王，并把每个时刻结束后的票王存起来；查询时二分最后一个 <= t 的时刻，直接取当时的票王。
// 时间复杂度：构造 O(n)，单次查询 O(log n)；空间复杂度：O(n)，保存时间数组与每个时刻的票王快照。
class TopVotedCandidate {  // 题解类：构造完成后支持 q(t) 查询
public:  // 构造函数与查询接口对外可见
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {  // persons[i] 是在 times[i] 时刻投票的人；times 严格递增
        int n = persons.size();  // 投票记录条数，也等于时间点个数
        this->times = times;  // 把时间数组存成成员变量，供 q 查询时二分使用
        wins.resize(n);  // wins[i] 记录处理完第 i 条记录（即 times[i] 时刻之后）时的票王
        vector<int> cnt(n);  // 计数数组：cnt[p] 表示候选人 p 当前的得票数
        int cur = 0;  // 当前票王；初始值任意，第一张票进来就会被比较更新
        for (int i = 0; i < n; ++i) {  // 按时间顺序处理每一条投票记录
            int p = persons[i];  // 本时刻投票的候选人
            ++cnt[p];  // 该候选人的票数加一
            if (cnt[cur] <= cnt[p]) {  // 用 <= 是为了平票时也更新，题目要求取「最近获得选票」的人
                cur = p;  // 更新当前票王
            }  // 票王判断结束
            wins[i] = cur;  // 记录 times[i] 时刻之后的票王，供查询使用
        }  // 遍历结束
    }  // 构造函数结束

    int q(int t) {  // 查询 t 时刻（含 t 之前的所有投票）的票王
        int i = upper_bound(times.begin(), times.end(), t) - times.begin() - 1;  // 二分找第一个大于 t 的时刻，下标减一即最后一个 <= t 的时刻
        return wins[i];  // 直接读出该时刻的票王
    }

private:  // 以下为内部状态，不对外暴露
    vector<int> times;  // 投票时刻数组，严格递增所以可以二分
    vector<int> wins;  // 每个时刻结束时的票王快照
};  // 类定义结束

// 以下是 LeetCode 判题器自动生成的调用示例，原样保留，不属于题解逻辑
/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */