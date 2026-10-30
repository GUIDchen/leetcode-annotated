// 题目：352. 将数据流变为多个不相交区间（Data Stream as Disjoint Intervals）
// 思路：用 map 以左端点为键保存有序区间，插入 val 时定位左右邻居，分别处理“左右通吃合并 / 并入左 / 并入右 / 新建单点区间”四种情形。
// 时间复杂度：addNum 为 O(log n)、getIntervals 为 O(n)；空间复杂度：O(n)，n 为不同数字个数。
class SummaryRanges {  // 题目要求的有序区间数据结构类
private:  // 以下为内部成员
    map<int, vector<int>> mp;  // 有序表：键是区间左端点，值是 [左端点, 右端点]，按键升序保存所有区间

public:  // 以下为对外接口
    SummaryRanges() {  // 构造函数：mp 默认为空，无需额外初始化
    }  // 构造函数体为空

    void addNum(int val) {  // 加入一个数字 val，并与相邻区间合并
        auto r = mp.upper_bound(val);  // r 指向第一个左端点大于 val 的区间，即右邻居
        auto l = r == mp.begin() ? mp.end() : prev(r);  // l 指向左端点小于等于 val 的最近区间；不存在时用 end() 表示
        if (l != mp.end() && r != mp.end() && l->second[1] + 1 == val && r->second[0] - 1 == val) {  // 左右邻居都存在，且 val 恰好填上两段缝隙，可三合一
            l->second[1] = r->second[1];  // 合并后左区间的右端点延伸到右区间的右端点
            mp.erase(r);  // 右区间已被吸收，删除它的记录
        } else if (l != mp.end() && val <= l->second[1] + 1)  // 情形二：val 落在左区间内部或紧邻其右端，就并入左区间
            l->second[1] = max(val, l->second[1]);  // 右端点取两者较大值；val 在区间内部时保持不变
        else if (r != mp.end() && val >= r->second[0] - 1)  // 情形三：val 紧邻右区间左端或落在其内部，就并入右区间
            r->second[0] = min(val, r->second[0]);  // 左端点取两者较小值；val 在区间内部时保持不变
        else  // 情形四：val 与任何已有区间都不相邻
            mp[val] = {val, val};  // 以 val 为左右端点新建一个单点区间
    }  // addNum 结束

    vector<vector<int>> getIntervals() {  // 返回当前的全部区间
        vector<vector<int>> res;  // 结果容器
        for (auto& range : mp) res.push_back(range.second);  // 按键（即左端点）升序遍历，取值压入结果，天然有序且互不相交
        return res;  // 返回区间列表
    }  // getIntervals 结束
};  // 类定义结束

// 下面是 LeetCode 模板注释，仅演示对象的构造与调用方式
/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */