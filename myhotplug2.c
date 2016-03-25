#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>  // for task_struct
#include <linux/time.h>   // for using jiffies
#include <linux/timer.h>
#include <linux/cpu.h>
#include <linux/smpboot.h>

struct task_struct *my_hotplugd;

static void run_my_hotplugd(unsigned int cpu);
struct task_struct *tmp_tsk;

static struct smp_hotplug_thread my_hotplug_threads = {
        .store                  = &my_hotplugd,
        .thread_fn              = run_my_hotplugd,
        .thread_comm            = "my_hotplugd/%u",
};



static __init int spawn_my_hotplug_threads(void){

         BUG_ON(smpboot_register_percpu_thread(&my_hotplug_threads));
         return 0;
}



static void run_my_hotplugd(unsigned int cpu) {
	tmp_tsk = current;
        for_each_process(tmp_tsk){

	printk(KERN_INFO "Aditya: my_hotplugd/%u are up and running", cpu);
}
}

early_initcall(spawn_my_hotplug_threads);



