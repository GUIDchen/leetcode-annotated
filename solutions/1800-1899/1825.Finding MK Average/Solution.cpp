// 题目：1825. 求出 MK 平均值（Finding MK Average）
// 核心思路：用 lo/mid/hi 三个 multiset 分别保存窗口内最小的 k 个、中间部分、最大的 k 个元素，mid 同时维护元素和 s；每加入一个元素并淘汰最旧的元素后，把三个集合的大小调回 k / m-2k / k，平均值即 s/(m-2k)。
// 时间复杂度：每次 addElement 为 O(log m)，calculateMKAverage 为 O(1)；空间复杂度：O(m)，队列与三个有序集合合计最多 m 个元素。
class MKAverage {  // 题解类：维护最近 m 个数并计算 MK 平均值
public:  // 对外提供构造函数、addElement 与 calculateMKAverage
    MKAverage(int m, int k) {  // m：窗口大小；k：需要剔除的最小/最大元素个数
        this->m = m;  // 保存窗口大小 m
        this->k = k;  // 保存剔除个数 k
    }

    void addElement(int num) {  // 每次加入一个新元素
        if (lo.empty() || num <= *lo.rbegin()) {  // 比 lo 的最大值还小，说明它属于最小的 k 个
            lo.insert(num);  // 放进 lo 集合
        } else if (hi.empty() || num >= *hi.begin()) {  // 或者比 hi 的最小值还大，说明它属于最大的 k 个
            hi.insert(num);  // 放进 hi 集合
        } else {  // 既不最小也不最大，落在中间部分
            mid.insert(num);  // 放进 mid 集合
            s += num;  // mid 的和同步累加，供求平均值使用
        }

        q.push(num);  // 新元素入队，队首始终是窗口内最旧的元素
        if (q.size() > m) {  // 窗口元素超过 m 个时需要淘汰最旧元素
            int x = q.front();  // 取出队首的最旧元素 x
            q.pop();  // 从队列中弹出它
            if (lo.find(x) != lo.end()) {  // x 在 lo 集合里
                lo.erase(lo.find(x));  // 从 lo 中删除 x
            } else if (hi.find(x) != hi.end()) {  // 否则 x 在 hi 集合里
                hi.erase(hi.find(x));  // 从 hi 中删除 x
            } else {  // 否则 x 必定在 mid 集合里
                mid.erase(mid.find(x));  // 从 mid 中删除 x
                s -= x;  // 同时从 mid 的和里扣掉 x
            }
        }
        while (lo.size() > k) {  // lo 超过 k 个：把最大的多余额度挪到 mid
            int x = *lo.rbegin();  // 取出 lo 的最大值
            lo.erase(prev(lo.end()));  // 删除这个最大值
            mid.insert(x);  // 移入 mid
            s += x;  // mid 的和增加
        }
        while (hi.size() > k) {  // hi 超过 k 个：把最小的多余额度挪到 mid
            int x = *hi.begin();  // 取出 hi 的最小值
            hi.erase(hi.begin());  // 删除这个最小值
            mid.insert(x);  // 移入 mid
            s += x;  // mid 的和增加
        }
        while (lo.size() < k && mid.size()) {  // lo 不足 k 个：从 mid 借最小的元素补足
            int x = *mid.begin();  // 取 mid 的最小值
            mid.erase(mid.begin());  // 从 mid 中删除它
            s -= x;  // mid 的和减少
            lo.insert(x);  // 放入 lo
        }
        while (hi.size() < k && mid.size()) {  // hi 不足 k 个：从 mid 借最大的元素补足
            int x = *mid.rbegin();  // 取 mid 的最大值
            mid.erase(prev(mid.end()));  // 从 mid 中删除它
            s -= x;  // mid 的和减少
            hi.insert(x);  // 放入 hi
        }
    }

    int calculateMKAverage() {  // 计算最近 m 个数的 MK 平均值
        return q.size() < m ? -1 : s / (q.size() - k * 2);  // 元素不足 m 个返回 -1，否则用 mid 的和除以中间元素个数（m - 2k）
    }

private:  // 以下为私有成员变量
    int m, k;  // 窗口大小 m 与剔除个数 k
    long long s = 0;  // 中间部分元素之和，用 long long 防止溢出
    queue<int> q;  // 队列保存窗口内元素，用于按插入顺序淘汰最旧元素
    multiset<int> lo, mid, hi;  // 三个有序集合：最小的 k 个、中间部分、最大的 k 个
};  // 类定义结束

// 判题器实例化对象时的调用示例（下面的原注释原样保留）
/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */