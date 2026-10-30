// 题目：2526. 找到数据流中的连续整数（Find Consecutive Integers from a Data Stream）
// 思路：只维护「末尾连续等于 value 的个数」cnt；新元素等于 value 就加一，否则清零。
// 时间复杂度：O(1) 每次 consec 调用；空间复杂度：O(1)，只存 val、k、cnt 三个变量。
class DataStream {  // 题目要求的 DataStream 类
public:  // 对外可见的构造与查询接口
    DataStream(int value, int k) {  // 构造函数：value 是目标值，k 是要求的连续出现次数
        val = value;  // 保存目标值到成员变量
        this->k = k;  // 用 this 区分同名的构造函数参数 k 与成员变量 k
    }  // 构造函数体结束
// 空行，分隔构造与查询方法
    bool consec(int num) {  // 插入新数字 num，返回末尾是否至少有 k 个连续的 value
        cnt = num == val ? cnt + 1 : 0;  // 等于目标值则连续计数加一，否则计数清零（连续性被打断）
        return cnt >= k;  // 计数达到 k 说明末尾存在连续 k 个 value
    }  // consec 方法结束
// 空行，分隔公有接口与私有成员
private:  // 私有成员区：内部状态不对外暴露
    int cnt = 0;  // cnt 记录「末尾连续等于 val 的元素个数」，声明时先清零
    int val, k;  // val 是目标值，k 是要求的连续次数
};  // 类定义结束
// 空行，分隔类与判题器给的调用说明
/**  // 判题器调用说明（以下为题目自带注释）
 * Your DataStream object will be instantiated and called as such:  // 说明：对象会被这样实例化
 * DataStream* obj = new DataStream(value, k);  // 说明：这里创建 DataStream 对象
 * bool param_1 = obj->consec(num);  // 说明：这里调用 consec 查询
 */  // 说明注释结束