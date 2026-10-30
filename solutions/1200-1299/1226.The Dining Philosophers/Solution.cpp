// 题目：1226. 哲学家进餐（The Dining Philosophers）
// 思路：每次进餐用 std::scoped_lock 一次性同时锁住「左手叉」和「右手叉」两把互斥量，不会只拿一把就等待，从而不产生循环等待，彻底避免死锁。
// 时间复杂度：O(1) 的加锁与回调调用（未计锁竞争等待）；空间复杂度：O(1)，固定 5 把互斥量。
class DiningPhilosophers {  // 题目给定的哲学家类，判题器会创建它并并发调用 wantsToEat
public:  // 接口对外可见
    using Act = function<void()>;  // 给回调类型起别名：每个动作都是一个无参、无返回值的函数

    void wantsToEat(int philosopher, Act pickLeftFork, Act pickRightFork, Act eat, Act putLeftFork, Act putRightFork) {  // philosopher：哲学家编号 0..4；后 5 个参数是题目提供的「拿左叉/拿右叉/吃/放左叉/放右叉」回调
        /* 这一题实际上是用到了C++17中的scoped_lock知识。  // 原题自带注释：这里用到 C++17 的 scoped_lock
                   作用是传入scoped_lock(mtx1, mtx2)两个锁，然后在作用范围内，依次顺序上锁mtx1和mtx2；然后在作用范围结束时，再反续解锁mtx2和mtx1。  // 原题自带注释：scoped_lock 接受多个锁，按给定顺序加锁，作用域结束时逆序解锁
                   从而保证了philosopher1有动作的时候，philosopher2无法操作；但是philosopher3和philosopher4不受影响 */  // 原题自带注释：于是相邻的两位哲学家不会同时操作，避免了互相等叉子的死锁
        std::scoped_lock lock(mutexes_[philosopher], mutexes_[philosopher >= 4 ? 0 : philosopher + 1]);  // 一次锁住本哲学家的左叉与右叉；编号 4 的哲学家右手边是 0 号叉子，所以用三元表达式取到 0
        pickLeftFork();  // 先报告拿起左叉（此时两把叉子都已经在手）
        pickRightFork();  // 再报告拿起右叉
        eat();  // 进餐
        putLeftFork();  // 放下左叉
        putRightFork();  // 放下右叉
    }  // 方法结束（作用域结束，scoped_lock 自动释放两把叉子）

private:  // 私有成员：叉子（互斥量）只属于本对象，外部不可访问
    vector<mutex> mutexes_ = vector<mutex>(5);  // 5 把叉子对应 5 个互斥量；mutex 不可拷贝，所以在声明处直接构造 vector
};  // 类定义结束