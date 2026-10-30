# 题目：1279. 红绿灯路口（Traffic Light Controlled Intersection）
# 思路：用一把互斥锁把「判断并切换信号灯 + 放行车辆」整体串行化，保证同一时刻只有一个方向的车能进入路口。
# 时间复杂度：O(1)，每次调用只有常数次判断与加解锁；空间复杂度：O(1)，只保存一把锁和当前绿灯方向。
from threading import Lock  # 引入互斥锁，用于串行化对信号灯状态的读写


class TrafficLight:  # 模拟红绿灯路口的类（多线程场景）
    def __init__(self):  # 初始化路口状态
        self.lock = Lock()  # 互斥锁：保证「判断方向 + 变灯 + 通行」这组操作的原子性
        self.road = 1  # 当前绿灯所在道路，1 表示 A 路，2 表示 B 路

    # 车辆到达路口时调用的方法：carId 为车辆编号，roadId 为所在道路，direction 为行驶方向
    def carArrived(
        self,  # 当前 TrafficLight 实例
        carId: int,  # ID of the car
        # ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        roadId: int,  # 车辆所在道路：1 为 A 路，2 为 B 路
        direction: int,  # Direction of the car
        # Use turnGreen() to turn light to green on current road
        turnGreen: 'Callable[[], None]',
        # Use crossCar() to make car cross the intersection
        crossCar: 'Callable[[], None]',
    ) -> None:  # 返回 None；turnGreen 负责把当前道路变绿，crossCar 负责让车通过
        self.lock.acquire()  # 先加锁，避免其他线程同时判断或修改信号灯状态
        if self.road != roadId:  # 当前绿灯方向与车辆所在道路不一致，需要变灯
            self.road = roadId  # 记录新的绿灯方向
            turnGreen()  # 调用回调，把该道路切换为绿灯
        crossCar()  # 放行这辆车通过路口
        self.lock.release()  # 通行结束，释放锁让其他车辆继续
