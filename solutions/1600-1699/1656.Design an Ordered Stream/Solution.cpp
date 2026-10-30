// 题目：1656. 设计有序流（Design an Ordered Stream）
// 思路：用数组按 idKey 直接存 value，ptr 始终指向下一个应该输出的位置；每次插入后只要 ptr 处非空就连续输出并后移。
// 时间复杂度：每次 insert 均摊 O(1)，每个元素只输出一次；空间复杂度：O(n)，数组长度 n+1。
class OrderedStream {  // 有序流类
public:  // 对外接口
    OrderedStream(int n) {  // 构造函数：n 为流的总长度
        ptr = 1;  // 指针从 1 开始（idKey 是 1-based）
        data = vector<string>(n + 1);  // 开 n+1 个槽位，下标 0 空置
    }  // 构造结束

    vector<string> insert(int idKey, string value) {  // 插入 (idKey, value)，返回本次能按序输出的片段
        data[idKey] = value;  // 按 idKey 直接落位
        vector<string> ans;  // 存放本次连续输出的结果
        while (ptr < data.size() && !data[ptr].empty()) {  // ptr 不越界且当前槽位有值，说明可以继续连续输出
            ans.push_back(data[ptr++]);  // 取出该值并让 ptr 后移（后置 ++ 保证先取旧值）
        }  // 连续输出结束
        return ans;  // 返回这段有序结果
    }  // insert 方法结束

private:  // 私有成员
    int ptr;  // 下一个待输出的位置
    vector<string> data;  // 按 idKey 存储的字符串数组
};  // 类定义结束

// 下面是 LeetCode 判题器自带的调用示例注释，原样保留
/**
 * Your OrderedStream object will be instantiated and called as such:
 * OrderedStream* obj = new OrderedStream(n);
 * vector<string> param_1 = obj->insert(idKey,value);
 */
