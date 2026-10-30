# 题目：1257. 最小公共区域（Smallest Common Region）
# 思路：区域树里每个节点只有一个父区域，先用字典建出「子区域 → 父区域」的映射；把 region1 到根路径上的区域放进集合，再让 region2 沿父指针往上爬，第一个命中集合的节点就是最小公共祖先。
# 时间复杂度：O(L)，L 为所有区域名字的总数（建图）加上两条链的长度；空间复杂度：O(L)，需要存父子映射与祖先集合。
class Solution:  # LeetCode 约定的题解类
    def findSmallestRegion(  # regions：每个列表首元素是父区域、其余是它的子区域；region1/region2：待求公共区域的两个区域
        # 参数换行书写，仍是同一个方法的签名（续行由括号维持）
        self, regions: List[List[str]], region1: str, region2: str  # 形参：层级信息、两个待求区域
    ) -> str:  # 返回最小公共区域的名字
        g = {}  # g 建立「子区域 → 父区域」映射，每个区域至多一个父区域
        for r in regions:  # 逐条解析层级信息
            x = r[0]  # 每组第一个名字是父区域
            for y in r[1:]:  # r[1:] 是它的直接子区域
                g[y] = x  # 记录子区域到父区域的边
        s = set()  # s 用来存放 region1 到根路径上的所有区域
        x = region1  # 从 region1 出发沿父指针向上
        while x in g:  # 只要还有父区域就说明当前区域在路上（根不在 g 里，循环到此终止）
            s.add(x)  # 把当前区域记入集合
            x = g[x]  # 上移一层
        x = region2  # 换从 region2 出发向上寻找
        while x in g and x not in s:  # 只要还有父区域、且当前区域尚未命中 region1 的祖先链，就继续上爬
            x = g[x]  # 上移一层
        return x  # 停下时所在的区域即最小公共区域（可能是 region2 本身或其某个祖先）
