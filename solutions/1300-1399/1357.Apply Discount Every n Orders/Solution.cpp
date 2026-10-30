// 题目：1357. 每隔 n 个顾客打折（Apply Discount Every n Orders）
// 思路：用哈希表建立「商品编号 → 单价」的映射，并用计数器对 n 取模判断当前顾客是否为第 n 位，是则按折扣比例减免。
// 时间复杂度：构造函数 O(m)，getBill 为 O(k)（k 为本次购买的商品种数）；空间复杂度：O(m)，m 为商品总数。
class Cashier {  // 收银台类：需要跨次调用保存顾客计数与商品价格表
public:  // 下列数据成员与接口对外可见
    int i;  // 已接待顾客数对 n 取模后的值，为 0 表示刚满一个周期
    int n;  // 折扣周期：每 n 位顾客打一次折
    int discount;  // 折扣百分比
    unordered_map<int, int> d;  // 商品编号 → 单价的哈希表，供每次结账快速查价

    Cashier(int n, int discount, vector<int>& products, vector<int>& prices) {  // 构造函数：初始化计数器并建立价格表
        this->i = 0;  // 顾客计数从 0 开始
        this->n = n;  // 保存折扣周期
        this->discount = discount;  // 保存折扣比例
        for (int j = 0; j < products.size(); j++) {  // 遍历所有商品，逐个建立编号与单价的映射
            d[products[j]] = prices[j];  // products[j] 的单价就是 prices[j]
        }  // 价格表建立完毕
    }  // 构造函数结束

    double getBill(vector<int> product, vector<int> amount) {  // 计算本次账单：product 是商品编号列表，amount 是对应数量列表
        i = (i + 1) % n;  // 顾客序号自增；取模结果为 0 说明这位顾客正好是第 n 位，可享折扣
        double x = 0;  // 未打折前的账单总额，用 double 保证后续能算折扣
        for (int j = 0; j < product.size(); j++) {  // 逐个商品累加金额
            x += d[product[j]] * amount[j];  // 账单金额 += 单价 × 数量
        }  // 累加完成
        if (i == 0) {  // 本顾客是第 n 位，需要打折
            return x - (discount * x) / 100.0;  // 减去折扣部分；除以 100.0 触发浮点除法，避免整数截断
        }  // 不打折时走下面的返回
        return x;  // 原价返回
    }  // getBill 结束
};  // 类定义结束

/**  // 下面是 LeetCode 判题器给出的调用示例，属于模板注释，原样保留
 * Your Cashier object will be instantiated and called as such:
 * Cashier* obj = new Cashier(n, discount, products, prices);
 * double param_1 = obj->getBill(product,amount);
 */