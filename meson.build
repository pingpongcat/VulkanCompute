project('VulkanCompute', 'c', default_options : ['c_std=c99'])
vlk_dep = dependency('Vulkan')
src = ['main.c',
    'compute.c',
    'instance.c',
    'device.c',
    'pipeline.c']

executable('VulkanCompute', src, dependencies : vlk_dep)

cs = run_command('glslangValidator', '-V', 'shader.comp', '-o', './build/shader.spv')

# Compile shaders and move them do build directory
if cs.returncode() != 0
    print('Could not comile shaders')
endif

output = cs.stdout().strip()
errortxt = cs.stderr().strip()
