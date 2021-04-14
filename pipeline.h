#if !defined(PIPELINE_H)
#define PIPELINE_H

extern VkPipeline Pipeline;
extern VkPipelineLayout PipelineLayout;

void DestroyPipeline(void);
void CreatePipeline(void);

#endif // PIPELINE_H

