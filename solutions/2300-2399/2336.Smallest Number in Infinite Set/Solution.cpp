// 题目：2336. 无限集中的最小数字（Smallest Number in Infinite Set）
// 核心思路：用有序集合保存「当前还在集合里的正整数」，既然题目保证最多调用 1000 次，初始只需装入 1..1000；取最小值取集合首元素，放回就是插入。
// 时间复杂度：构造 O(1000 log 1000)，popSmallest/addBack 均为 O(log n)；空间复杂度：O(1000) 即 O(1)。
class SmallestInfiniteSet {  // 无限集合类：维护当前还可用的正整数
public:  // 以下为对外接口
    SmallestInfiniteSet() {  // 构造函数：初始化集合内容
        for (int i = 1; i <= 1000; ++i) {  // 题目保证总操作次数不超过 1000，所以只需装入 1..1000
            s.insert(i);  // 把 i 插入有序集合（set 会自动排序去重）
        }  // 初始化循环结束
    }  // 构造函数结束

    int popSmallest() {  // 弹出并返回集合中的最小数字
        int x = *s.begin();  // 有序集合的首元素就是最小值，解引用取到它的值
        s.erase(s.begin());  // 把这个最小值从集合中删除，模拟「被取出」
        return x;  // 返回刚取出的最小值
    }  // popSmallest 方法结束

    void addBack(int num) {  // 把一个之前被取出的数字放回集合
        s.insert(num);  // 直接插入即可；set 会去重并保持有序，重复插入不会出错
    }  // addBack 方法结束

private:  // 以下为内部私有数据
    set<int> s;  // 有序集合：始终能在对数量时间内拿到当前最小值
};  // SmallestInfiniteSet 类结束

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */