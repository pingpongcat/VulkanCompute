project('VulkanCompute', 'c', default_options : ['c_std=c11'])
vlk_dep = dependency('Vulkan')

src = ['main.c',
    'compute.c',
    'instance.c',
    'device.c',
    'pipeline.c']

executable('VulkanCompute', src, dependencies : vlk_dep)

compiler = meson.get_compiler('c')

if compiler.get_id() == 'gcc'
    message('Compiler: GCC')
elif compiler.get_id() == 'clang'
    message('Compiler: LLVM/clang')
endif

glsl_validator = 'glslangValidator'

# Compile shaders
cs = run_command(glsl_validator, '-V', 'shader.comp', '-o', './build/shader.spv')

if cs.returncode() != 0
    message('Could not comile shaders')
endif

output = cs.stdout().strip()
errortxt = cs.stderr().strip()
