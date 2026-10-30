// 题目：1146. 快照数组（Snapshot Array）
// 思路：每个下标维护一条按快照号递增的「(快照号, 值)」记录，set 只追加记录，get 用二分找到不超过 snap_id 的最后一条修改。
// 时间复杂度：set 为 O(1)，snap 为 O(1)，get 为 O(log L)（L 为该下标的修改次数）；空间复杂度：O(修改总次数)。
class SnapshotArray {  // 每个下标保存一条按快照号递增的修改记录
public:  // 对外接口
    SnapshotArray(int length) {  // 构造函数：length 是数组长度
        arr.resize(length);  // 为每个下标准备好空的记录数组
    }  // 构造结束

    void set(int index, int val) {  // 把 index 位置的值设为 val
        arr[index].emplace_back(i, val);  // 追加一条 (当前快照号, 值) 记录，保留历史而不是覆盖
    }  // set 结束

    int snap() {  // 拍一次快照，返回快照编号
        return i++;  // 先返回旧快照号，再自增
    }  // snap 结束

    int get(int index, int snap_id) {  // 查询 index 在快照 snap_id 时的值
        auto it = upper_bound(arr[index].begin(), arr[index].end(), make_pair(snap_id, INT_MAX));  // 二分找到第一条快照号严格大于 snap_id 的记录
        return it == arr[index].begin() ? 0 : prev(it)->second;  // 若没有更早的记录说明该位置从未修改过，值为 0；否则取上一条记录的值
    }  // get 结束

private:  // 内部数据成员
    vector<vector<pair<int, int>>> arr;  // arr[i] 保存下标 i 的修改历史
    int i = 0;  // 当前快照号，从 0 开始
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */