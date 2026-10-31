# Model Module Architecture

## 1. Module Overview

- **Function Description**: The Model module manages the execution model of computation graphs, covering full lifecycle management including model creation, Stream binding, task loading, model execution, and destruction. It supports two types: the normal model (Normal Model) and the capture model (Capture Model), and implements task scheduling and execution through the SQ/CQ mechanism.
- **Design Objectives**:
  - Provide a unified model management API
  - Support binding and scheduling of multiple Streams
  - Implement batch submission and execution of Tasks
  - Support Label allocation and jump control
  - Provide synchronous/asynchronous model execution modes

## 2. Usage Scenarios and External APIs

### 2.1 Usage Scenarios

- **Scenario 1**: Create and execute a computation model (using ACL APIs)
  ```cpp
  aclmdlRI modelRI;
  aclmdlRIBuildBegin(&modelRI, 0);  // Start building the model
  aclmdlRIBindStream(modelRI, stream, ACL_MODEL_STREAM_FLAG_HEAD);  // Bind a Stream
  // Add tasks to the stream
  aclmdlRIEndTask(modelRI, stream);  // Mark the end of tasks
  aclmdlRIBuildEnd(modelRI, nullptr);  // End the building
  aclmdlRIExecute(modelRI, -1);  // Execute synchronously
  aclmdlRIDestroy(modelRI);  // Destroy the model
  ```

- **Scenario 2**: Execute a model asynchronously (using ACL APIs)
  ```cpp
  aclmdlRIExecuteAsync(modelRI, execStream);
  // Synchronize on the Stream to wait for execution completion
  aclrtSynchronizeStream(execStream);
  ```

### 2.2 External APIs

| ACL API | File Location | Description |
|----------|----------|------|
| `aclmdlRIBuildBegin()` | `include/external/acl/acl_rt.h`<br>`src/acl/aclrt_impl/model_ri.cpp` | Creates a model (starts building). |
| `aclmdlRIDestroy()` | `include/external/acl/acl_rt.h`<br>`src/acl/aclrt_impl/model_ri.cpp` | Destroys a model. |
| `aclmdlRIBindStream()` | `include/external/acl/acl_rt.h`<br>`src/acl/aclrt_impl/model_ri.cpp` | Binds a Stream to the model. |
| `aclmdlRIUnbindStream()` | `include/external/acl/acl_rt.h`<br>`src/acl/aclrt_impl/model_ri.cpp` | Unbinds a Stream. |
| `aclmdlRIExecute()` | `include/external/acl/acl_rt.h`<br>`src/acl/aclrt_impl/model_ri.cpp` | Executes a model synchronously. |
| `aclmdlRIExecuteAsync()` |`include/external/acl/acl_rt.h`<br>`src/acl/aclrt_impl/model_ri.cpp` | Executes a model asynchronously. |
| `aclmdlRIBuildEnd()` | `include/external/acl/acl_rt.h`<br>`src/acl/aclrt_impl/model_ri.cpp` | Completes model building (LoadComplete). |
| `aclmdlRIEndTask()` | `include/external/acl/acl_rt.h`<br>`src/acl/aclrt_impl/model_ri.cpp` | Marks the end of tasks. |
| `aclmdlRISetName()` | `include/external/acl/acl_rt.h`<br>`src/acl/aclrt_impl/model_ri.cpp` | Sets the model name. |
| `aclmdlRIAbort()` |`include/external/acl/acl_rt.h`<br>`src/acl/aclrt_impl/model_ri.cpp` | Aborts model execution. |

## 3. Architecture Overview

### 3.1 Overall Design Ideas

The Model adopts a two-layer inheritance structure: the base class Model provides the complete functions of a normal model. Each Model binds multiple Streams, submits execution tasks through ModelExecuteTask, and uses Notify to implement execution completion notification.

| Design Point | Description |
|--------|------|
| **Model as the task container** | Binds multiple Streams and manages SQE dispatching and execution in a unified manner. |
| **Stream as the task queue** | Each Stream maintains an SQ task sequence and supports task reclamation. |
| **Label implements control flow** | The Model allocates Label IDs, and Streams record jump points. |
| **headStreams mechanism** | Marks entry Streams, from which execution is activated during Execute. |
| **Execution flow mechanism** | Dispatches model execution tasks and activates model stream execution. |

### 3.2 Architecture Layering Diagram

```mermaid
graph TB
    subgraph ContextLayer["Context Runtime Environment"]
        Context["Context<br/>Manages multiple Models"]
    end
    
    subgraph ModelLayer["Model Core Container"]
        Model["Model<br/>Computation graph container"]
        ModelStreams["streams_<br/>All bound Streams"]
        ModelHeadStreams["headStreams_<br/>Entry Streams"]
        ModelLabelMap["labelMap_<br/>Label ID → Label"]
        ModelLabelAllocator["labelAllocator_<br/>Label ID allocator"]
        ModelArgRecord["argLoaderRecord_<br/>Parameter handle records"]
        
        Model --> ModelStreams
        Model --> ModelHeadStreams
        Model --> ModelLabelMap
        Model --> ModelLabelAllocator
        Model --> ModelArgRecord
    end
    
    subgraph StreamLayer["Stream Task Queue Layer"]
        Stream1["Stream 1<br/>Task queue"]
        Stream2["Stream 2<br/>Task queue"]
        Stream3["Stream 3<br/>Slave Stream"]
        
        StreamModel["Model*<br/>Backward reference"]
        StreamTasks["delayRecycleTaskid_<br/>Task ID list"]
        StreamSQ["SQ Queue<br/>Task execution queue"]
        StreamCQ["CQ Queue<br/>Completion queue"]
        StreamAutoSplit["AutoSplitSqContext<br/>Auto-split context"]
        
        Stream1 --> StreamModel
        Stream1 --> StreamTasks
        Stream1 --> StreamSQ
        Stream1 --> StreamCQ
        
        Stream3 --> StreamAutoSplit
    end
    
    subgraph LabelLayer["Label Control Flow Layer"]
        Label1["Label 1"]
        Label2["Label 2"]
        
        LabelModel["Model*<br/>Owning Model"]
        LabelStream["Stream*<br/>Host Stream"]
        LabelId["labelId_<br/>Allocated by the Model"]
        LabelDevAddr["devDstAddr_<br/>Device jump address"]
        
        Label1 --> LabelModel
        Label1 --> LabelStream
        Label1 --> LabelId
        Label1 --> LabelDevAddr
    end
    
    subgraph TaskLayer["Task Layer"]
        TaskInfo["TaskInfo<br/>Task information"]
        TaskId["id: Task ID"]
        TaskPos["pos: SQE position"]
        TaskStream["Stream*<br/>Owning Stream"]
        TaskUpdateFlag["updateFlag<br/>KEEP/UPDATE/DISABLE"]
        
        TaskInfo --> TaskId
        TaskInfo --> TaskPos
        TaskInfo --> TaskStream
        TaskInfo --> TaskUpdateFlag
    end
    
    %% Relationship edges
    Context --> Model
    
    ModelStreams --> Stream1
    ModelStreams --> Stream2
    ModelStreams --> Stream3
    ModelHeadStreams --> Stream1
    
    ModelLabelMap --> Label1
    ModelLabelMap --> Label2
    ModelLabelAllocator --> LabelId
    
    StreamTasks --> TaskInfo
    TaskStream --> Stream1
    
    %% Jump relationship between Stream and Label
    LabelStream -.Jump.-> Stream2
    
    %% AutoSplitSq relationships
    StreamAutoSplit -.Master/Slave.-> Stream1
    StreamAutoSplit -.Slave.-> Stream3
```

### 3.3 Model-Stream-Label Three-Layer Architecture Relationship

```mermaid
graph LR
    subgraph Layer1["Layer 1: Model Container"]
        ModelContainer["Model<br/><b>Core responsibilities</b><br/>1. Bind multiple Streams<br/>2. Allocate Label IDs<br/>3. Manage SQE dispatching<br/>4. Manage execution entries"]
    end
    
    subgraph Layer2["Layer 2: Stream Queue"]
        StreamQueue["Stream<br/><b>Core responsibilities</b><br/>1. Maintain the SQ task queue<br/>2. Record the task ID list<br/>3. Reference the Model backward<br/>4. Support task reclamation"]
    end
    
    subgraph Layer3["Layer 3: Label Control Flow"]
        LabelCtrl["Label<br/><b>Core responsibilities</b><br/>1. Set jump targets<br/>2. Implement cross-stream jumps<br/>3. Control flow branches<br/>4. Loop control"]
    end
    
    %% Inter-layer relationships
    ModelContainer -->|"Binds"| StreamQueue
    ModelContainer -->|"Allocates"| LabelCtrl
    StreamQueue -->|"Sets the jump point"| LabelCtrl
    LabelCtrl -->|"Jumps"| StreamQueue
    
    %% Backward references
    StreamQueue -.Backward reference.-> ModelContainer
    LabelCtrl -.Backward reference.-> ModelContainer
```

### 3.4 Interaction Diagrams of Core Modules (Including Hardware Interaction)

This section uses sequence diagrams to show the key differences between the AutoSplit and non-AutoSplit scenarios.

#### 3.4.1 Stream Binding Phase

```mermaid
sequenceDiagram
    participant App as Application
    participant ACL as ACL API Layer
    participant RT as Runtime API Layer
    participant Model as Model Container
    participant Stream as Stream Queue
    participant Device as Device Management
    participant Driver as Driver Layer
    participant HW as Hardware Layer<br/>TS/SQ/CQ

    Note over App,HW: Stream Binding Phase
    App->>ACL: aclmdlRIBindStream(modelRI, stream)
    ACL->>RT: rtModelBindStream()
    RT->>RT: Check Model.IsAutoSplitSq()
    
    %% AutoSplit path
    alt AutoSplit mode (supports unlimited queue depth)
        RT->>Model: ModelAddStream(mdl, stm, flag)
        Model->>Stream: SetModel(this)
        Model->>Model: streams_.push_back(stream)
        Note right of Model: Binding on the Runtime side only<br/>Hardware tasks are not submitted immediately
        Model-->>RT: Binding succeeded (software side)
        RT-->>ACL: success
        ACL-->>App: ACL_SUCCESS
    else Non-AutoSplit mode (traditional GE model)
        RT->>Model: BindStream(stream)
        Model->>Stream: SetModel(this)
        Stream-->>Model: bindFlag=true
        Model->>Device: SubmitTask(ModelMaintainceTask)
        Device->>Driver: SubmitTask(taskInfo)
        Driver->>HW: Write to SQ<br/>MSG: MMT_STREAM_ADD
        HW-->>Driver: CQE (completion response)
        Driver-->>Device: RT_ERROR_NONE
        Device-->>Model: Binding succeeded
        Model-->>RT: streams_ updated
        RT-->>ACL: success
        ACL-->>App: ACL_SUCCESS
    end
```

**Difference Description**:
| Comparison Item | AutoSplit Mode | Non-AutoSplit Mode |
|--------|----------------|-------------------|
| Binding timing | Software binding on the Runtime side only | Hardware binding tasks are submitted immediately |
| Hardware interaction | The hardware relationship is established at LoadComplete | SQ is written immediately at binding |
| Task queue | Host SQE buffer (expandable) | Fixed hardware SQ |

#### 3.4.2 Task Submission Phase

```mermaid
sequenceDiagram
    participant App as Application
    participant ACL as ACL API Layer
    participant RT as Runtime API Layer
    participant Stream as Stream Queue
    participant AutoSplitCtx as AutoSplitSqContext
    participant SlaveStream as Slave Stream
    participant Device as Device Management
    participant HW as Hardware Layer<br/>SQ

    Note over App,HW: Task Submission Phase
    App->>ACL: rtKernelLaunch(kernel, stream)
    ACL->>RT: rtKernelLaunch()
    RT->>Stream: Check IsAutoSplitSq()
    
    %% AutoSplit path
    alt AutoSplit mode
        RT->>Stream: StreamLock()
        Stream->>AutoSplitCtx: GetAutoSplitCtx()
        AutoSplitCtx-->>Stream: curStreamSqeCount, slaveStreams
        
        %% Check whether the capacity requires creating a Slave Stream
        Stream->>Stream: Check curStreamSqeCount + sqeNum > HOST_SQ_MAX_COUNT
        alt Insufficient capacity (close to 32K)
            Stream->>RT: CreateAutoSplitSlaveStream(masterStream)
            RT->>SlaveStream: new SlaveStream()
            SlaveStream->>SlaveStream: SetupForAutoSplit()
            SlaveStream->>Device: AllocSqCqForAutoSplit()
            Device-->>SlaveStream: sqId, cqId
            Stream->>AutoSplitCtx: slaveStreams.push_back(slaveStream)
            Stream->>SlaveStream: CondStreamActive(slaveStream, prevStream)
            Note right of SlaveStream: Automatically create a Slave Stream<br/>to expand the queue capacity
        else Sufficient capacity
            Note right of Stream: Use the current Master/Slave Stream
        end
        
        %% Allocate tasks and write to the Host Buffer
        Stream->>Stream: AllocTaskInfoOnAutoSplitStream()
        Stream->>AutoSplitCtx: curStreamSqeCount += sqeNum
        Stream->>Stream: Write SQEs to sqeBuffer_ (Host memory)
        Note right of Stream: SQEs are temporarily stored in the Host Buffer<br/>and are not directly written to the hardware SQ
        Stream->>Stream: StreamUnLock()
        Stream-->>RT: TaskInfo
        RT-->>ACL: success
        ACL-->>App: ACL_SUCCESS
    else Non-AutoSplit mode
        RT->>Stream: AllocTask()
        Stream->>Stream: Record to delayRecycleTaskid_
        Stream->>Stream: Write SQEs directly to the hardware SQ
        Stream->>HW: Write SQEs directly to the hardware SQ
        HW-->>Stream : success
        Stream-->>RT: success
        RT-->>ACL: success
        ACL-->>App: ACL_SUCCESS
    end
```

**Difference Description**:
| Comparison Item | AutoSplit Mode | Non-AutoSplit Mode |
|--------|----------------|-------------------|
| SQE storage location | Host sqeBuffer_ | Device SQ |
| Capacity limit | Unlimited (expanded by Slave Streams) | Fixed depth |
| Submission timing | Dispatched in batches at LoadComplete | Real-time submission |
| Slave Stream | Automatically created when tasks are close to 32K | Not supported |

#### 3.4.3 EndGraph Marking Phase

```mermaid
sequenceDiagram
    participant App as Application
    participant ACL as ACL API Layer
    participant RT as Runtime API Layer
    participant Stream as Stream Queue
    participant Model as Model Container
    participant Notify as Notify Synchronization Object
    participant Device as Device Management
    participant Driver as Driver Layer
    participant HW as Hardware Layer<br/>SQ/CQ

    Note over App,HW: EndGraph Marking Phase
    App->>ACL: aclmdlRIEndTask(modelRI, stream)
    ACL->>RT: rtEndGraph()
    
    %% AutoSplit path
    alt AutoSplit mode
        RT->>Stream: AllocTaskInfoOnAutoSplitStream()
        Stream->>Stream: Create a Notify object and apply for notifyId
        Stream->>Model: endGraphNotify_ = Notify(notifyId)
        Stream->>Stream: Write SQEs to sqeBuffer_
        Note right of Stream: The EndGraph SQE is temporarily stored in the Host Buffer<br/>and dispatched in batches at LoadComplete
        Stream-->>RT: success
        RT-->>ACL: success
        ACL-->>App: ACL_SUCCESS
    else Non-AutoSplit mode
        RT->>Stream: AddEndGraphTask()
        Stream->>Stream: Create a Notify object and apply for notifyId
        Stream->>Model: endGraphNotify_ = Notify(notifyId)
        Stream->>Device: SubmitTask(EndGraphTask)
        Device->>Driver: SubmitTask()
        Driver->>HW: Write to SQ<br/>MSG: END_GRAPH
        HW-->>Driver: CQE
        Driver-->>Device: success
        Device-->>Stream: success
        Stream-->>RT: EndGraph dispatched successfully
        RT-->>ACL: success
        ACL-->>App: ACL_SUCCESS
    end
```

#### 3.4.4 LoadComplete Phase

```mermaid
sequenceDiagram
    participant App as Application
    participant ACL as ACL API Layer
    participant RT as Runtime API Layer
    participant Model as Model Container
    participant Stream as Stream Queue
    participant SlaveStream as Slave Stream
    participant Device as Device Management
    participant Driver as Driver Layer
    participant HW as Hardware Layer<br/>TS/SQ/CQ

    Note over App,HW: LoadComplete Phase (key difference point)
    App->>ACL: aclmdlRIBuildEnd(modelRI)
    ACL->>RT: rtModelLoadComplete()
    RT->>Model: LoadComplete()
    Model->>Model: Check IsAutoSplitSq()
    
    %% AutoSplit path
    alt AutoSplit mode
        Note right of Model: Step 1: Allocate SQ/CQ for all Streams
        Model->>Model: BuildSqCqForAutoSplit()
        
        %% Traverse all Streams (including Slaves)
        loop Traverse StreamList_ (Master + Slave Streams)
            Model->>Stream: AllocAutoSplitSqAddr()
            Stream->>Device: AllocSqCqForAutoSplit()
            Device-->>Stream: sqId, sqAddr, sqDepth
            Stream->>Model: GetSqBaseAddr(), GetSqId()
            Model->>Model: modelSwitchInfo_[i].stream_id = streamId
            Model->>Model: modelSwitchInfo_[i].sq_id = sqId
        end
        
        %% Switch Streams to SQ in batches
        Note right of Model: Step 2: Switch Streams to SQ in batches
        Model->>Device: SqSwitchStreamBatch(modelSwitchInfo_, streamNum)
        Device->>Driver: SqSwitchStreamBatch(deviceId, info, num)
        Driver->>HW: MSG: SQ_SWITCH_STREAM_BATCH
        HW-->>Driver: success
        Driver-->>Device: success
        
        %% Send SQEs
        Note right of Model: Step 3: Dispatch SQEs to the device SQ in batches
        Model->>Model: SendSqe()
        Model->>Device: Traverse StreamList_
        Device->>Driver: StreamTaskFill(deviceId, streamId, sqAddr, sqeBuffer, sqeNum)
        Driver->>HW: Write to SQ in batches<br/>MSG: SQE_BATCH
        HW-->>Driver: CQE_BATCH
        Driver-->>Device: RT_ERROR_NONE
        
        %% Bind Streams to the Model
        Note right of Model: Step 4: Bind Streams to the Model (hardware side)
        loop Traverse StreamList_
            Model->>Device: EnterBindStream(stm, streamFlag)
            Device->>Driver: SubmitTask(ModelMaintainceTask)
            Driver->>HW: MSG: MMT_STREAM_ADD
            HW-->>Driver: CQE
            Model->>Stream: SetIsTsBind(true)
        end
        
        %% Configure SQ Tail
        Note right of Model: Step 5: Configure the SQ Tail pointer
        Model->>Model: ConfigSqTail()
        Model->>Device: SetSqTail(deviceId, tsId, sqId, sqTailPos)
        Device->>Driver: SetSqTail()
        Driver->>HW: MSG: SQ_TAIL_UPDATE
        HW-->>Driver: success
        
        Model->>Model: isModelComplete_=true
        Model-->>RT: success
        RT-->>ACL: success
        ACL-->>App: ACL_SUCCESS
    else Non-AutoSplit mode
        Note right of Model: Traverse StreamList_ directly and dispatch in batches
        Model->>Model: SendSqe()
        Model->>Device: Traverse StreamList_
        Device->>Driver: StreamTaskFill(deviceId, streamId, sqAddr, sqeBuffer, sqeNum)
        Driver->>HW: Write to SQ in batches<br/>MSG: SQE_BATCH<br/>DATA: [SQE1, SQE2, ...]
        HW-->>Driver: CQE_BATCH
        Driver-->>Device: RT_ERROR_NONE
        Model->>Device: ConfigSqTail()
        Device->>Driver: SetSqTail(deviceId, tsId, sqId, sqTailPos)
        Driver->>HW: Configure SQ Tail<br/>MSG: SQ_TAIL_UPDATE
        HW-->>Driver: success
        Driver-->>Device: success
        Device-->>Model: success
        Model->>Model: isModelComplete_=true
        Model-->>RT: success
        RT-->>ACL: success
        ACL-->>App: ACL_SUCCESS
    end
```

**Difference Description**:
| Comparison Item | AutoSplit Mode | Non-AutoSplit Mode |
|--------|----------------|-------------------|
| SQ/CQ allocation | Dynamically allocated at LoadComplete | Already allocated at Stream creation |
| Stream switching | Switched in batches by SqSwitchStreamBatch | No switching required |
| Hardware binding | The hardware relationship is established at LoadComplete | Already established at binding |
| Slave Stream | All Masters + Slaves need to be processed | Only bound Streams are processed |

#### 3.4.5 Model Execution Phase

```mermaid
sequenceDiagram
    participant App as Application
    participant ACL as ACL API Layer
    participant RT as Runtime API Layer
    participant Model as Model Container
    participant Stream as Stream Queue
    participant Notify as Notify Synchronization Object
    participant Device as Device Management
    participant Driver as Driver Layer
    participant HW as Hardware Layer<br/>TS/SQ/CQ
    
    Note over App,HW: Phase: Model execution (unified flow for AutoSplit and non-AutoSplit)
    App->>ACL: aclmdlRIExecute(modelRI)
    ACL->>RT: rtModelExecute()
    RT->>Model: ExecuteSync()
    Model->>Model: SubmitExecuteTask()
    Model->>Device: SubmitTask(ModelExecuteTask)
    Device->>Driver: SubmitTask(exeTask)
    Driver->>HW: Write to SQ<br/>MSG: MODEL_EXECUTE<br/>DATA: modelId, headStreams
    Driver->>HW: Activate the TS hardware
    HW->>HW: The hardware scheduler reads SQEs from SQ
    HW->>HW: AICore/AIVector performs computation
    HW->>HW: Write to CQ<br/>MSG: CQE_COMPLETION<br/>DATA: taskId, errorCode
    HW-->>Driver: CQE (execution completed)
    Driver-->>Device: completion event
    Device-->>Notify: Trigger endGraphNotify_
    Notify->>Notify: Notify::Signal()
    Model->>Notify: NtyWait(endGraphNotify_, stream)
    Notify-->>Model: wait success
    Model->>Stream: Synchronize()
    Stream->>Device: StreamSync()
    Device->>Driver: GetCqHead()
    Driver->>HW: Read CQ<br/>MSG: CQ_POLL
    HW-->>Driver: CQ status
    Driver-->>Device: all completed
    Device-->>Stream: sync success
    Stream-->>Model: execution done
    Model-->>RT: success
    RT-->>ACL: success
    ACL-->>App: ACL_SUCCESS
```

**Description**: In the model execution phase, the AutoSplit and non-AutoSplit flows are unified. The difference lies in the SQE source:
- AutoSplit: SQEs have been dispatched in batches from the Host Buffer to the device SQ at LoadComplete
- Non-AutoSplit: SQEs have been directly written to the device SQ at task submission

#### 3.4.6 Model Destruction Phase

```mermaid
sequenceDiagram
    participant App as Application
    participant ACL as ACL API Layer
    participant RT as Runtime API Layer
    participant Model as Model Container
    participant Stream as Master Stream
    participant SlaveStream as Slave Stream
    participant Notify as Notify Synchronization Object
    participant Device as Device Management
    participant Driver as Driver Layer
    participant HW as Hardware Layer<br/>SQ/CQ

    Note over App,HW: Model Destruction Phase
    App->>ACL: aclmdlRIDestroy(modelRI)
    ACL->>RT: rtModelDestroy()
    RT->>Model: TearDown()
    
    %% AutoSplit path
    alt AutoSplit mode
        Note right of Model: All Slave Streams must be unbound first
        Model->>Stream: GetAutoSplitCtx()
        Stream-->>Model: autoSplitCtx->slaveStreams
        loop Traverse Slave Streams
            Model->>SlaveStream: UnbindStream(slaveStream)
            SlaveStream->>Device: ModelUnBindTaskSubmit()
            Device-->>SlaveStream: Unbinding succeeded
        end
        Model->>Stream: UnbindStream(masterStream)
        Model->>Notify: DELETE_O(endGraphNotify_)
        Model->>Model: ClearMemory()
        Model->>Device: SubmitTask(ModelDestroyTask)
        Device->>Driver: SubmitTask()
        Driver->>HW: MSG: MODEL_DESTROY
        HW-->>Driver: CQE
        Model-->>RT: destroyed
        RT-->>ACL: success
        ACL-->>App: ACL_SUCCESS
    else Non-AutoSplit mode
        Model->>Notify: DELETE_O(endGraphNotify_)
        Model->>Model: ClearMemory()
        Model->>Device: SubmitTask(ModelDestroyTask)
        Device->>Driver: SubmitTask()
        Driver->>HW: Write to SQ<br/>MSG: MODEL_DESTROY
        HW-->>Driver: CQE
        Driver-->>Device: destroyed
        Device-->>Model: destroyed
        Model-->>RT: destroyed
        RT-->>ACL: success
        ACL-->>App: ACL_SUCCESS
    end
```

## 4. Detailed Design

### 4.1 Core Flows

#### Model Creation and Initialization Flow

```mermaid
flowchart TD
    A["The user calls aclmdlRIBuildBegin()"] --> B["Create a Model object"]
    B --> C["Initialize basic attributes<br/>modelId, name"]
    C --> D["Create core management objects"]
    D --> E["Allocate LabelAllocator<br/>for control flow jumps"]
    D --> F["Create a Notifier<br/>for execution completion notification"]
    E --> H["Prepare argLoaderRecord_<br/>for parameter handle management"]
    F --> H
    H --> I["The Model object is ready<br/>"]
    
    style A fill:#e1f5ff
    style I fill:#c8e6c9
```

**Flow Description**:
1. The user initiates a model creation request through ACL APIs.
2. The Runtime creates the Model object and allocates a unique modelId.
3. The Runtime initializes the Label allocator to support subsequent branch jump control.
4. The Runtime creates the Notifier object for the notification mechanism after model execution completes.
5. The Runtime applies for device-side memory to store model metadata.
6. The Runtime prepares the parameter handle record table to manage task parameter memory.

#### Stream Binding Flow

```mermaid
flowchart TD
    A["The user calls aclmdlRIBindStream()"] --> B["Check the Stream state"]
    B --> C{"Is the Stream already bound?"}
    C -->|Bound| D["Return an error<br/>Repeated binding is not allowed"]
    C -->|Unbound| J{"Does the Model enable AutoSplit?"}
    
    %% AutoSplit path
    J -->|Yes, AutoSplit mode| E1["Add to the Model streams_ list<br/>Binding on the Runtime side only"]
    E1 --> F1{"Is it a head Stream?"}
    F1 -->|Yes| G1["Add to headStreams_<br/>as the model execution start point"]
    F1 -->|No| H1["Add only to streams_<br/>as a normal execution flow"]
    G1 --> I1["Establish bidirectional references between model and stream"]
    H1 --> I1
    I1 --> O1["Binding completed (software side)<br/>Wait for LoadComplete to establish the hardware relationship"]
    
    %% Non-AutoSplit path
    J -->|No, non-AutoSplit mode| E2["Add to the Model streams_ list"]
    E2 --> F2{"Is it a head Stream?"}
    F2 -->|Yes| G2["Add to headStreams_<br/>as the model execution start point"]
    F2 -->|No| H2["Add only to streams_<br/>as a normal execution flow"]
    G2 --> I2["Establish bidirectional references between model and stream"]
    H2 --> I2
    I2 --> K2["Create the maintenance task<br/>ModelMaintainceTask"]
    K2 --> L2["Submit the task to the device"]
    L2 --> M2["The hardware confirms the binding succeeded<br/>and returns a CQE"]
    M2 --> O2["Binding completed<br/>Task submission can start"]
    
    style A fill:#e1f5ff
    style D fill:#ffcdd2
    style O1 fill:#fff3e0
    style O2 fill:#c8e6c9
```

**Flow Description**:

| Step | AutoSplit Mode | Non-AutoSplit Mode |
|------|----------------|-------------------|
| 1 | The user requests binding a Stream to the Model | The user requests binding a Stream to the Model |
| 2 | Check the Stream state to prevent repeated binding | Check the Stream state to prevent repeated binding |
| 3 | Add to the streams_ list on the Runtime side only | Add to the streams_ list |
| 4 | Determine whether it is a head Stream | Determine whether it is a head Stream |
| 5 | Establish bidirectional references | Establish bidirectional references |
| 6 | **Hardware tasks are not submitted immediately** | Create the maintenance task and notify the hardware |
| 7 | **Wait for LoadComplete** | Submit the task to the device, and the hardware returns a CQE |
| 8 | Binding completed (software side) | Binding completed; task submission can start |

**Key Difference**: In AutoSplit mode, Stream binding only completes the software-side record, and hardware binding is deferred to the LoadComplete phase. This enables more flexible task queue management.

#### Task Submission Flow

```mermaid
flowchart TD
    A["The user calls rtKernelLaunch()"] --> B["Obtain the target Stream"]
    B --> J{"Does the Stream enable AutoSplit?"}
    
    %% AutoSplit path
    J -->|Yes, AutoSplit mode| E1["Obtain AutoSplitSqContext"]
    E1 --> F1{"Check curStreamSqeCount + sqeNum > HOST_SQ_MAX_COUNT?"}
    
    %% Insufficient capacity; create a Slave Stream
    F1 -->|Yes, insufficient capacity| G1["Create an AutoSplit Slave Stream"]
    G1 --> H1["SlaveStream.SetupForAutoSplit()"]
    H1 --> I1["Allocate new SQ/CQ"]
    I1 --> K1["Add to the slaveStreams list"]
    K1 --> L1["CondStreamActive(slave, prevStream)"]
    L1 --> M1["Use the currently active Stream (Master or Slave)"]
    
    %% Sufficient capacity
    F1 -->|No, sufficient capacity| M1["Use the currently active Stream"]
    
    M1 --> N1["AllocTaskInfoOnAutoSplitStream()"]
    N1 --> O1["curStreamSqeCount += sqeNum"]
    O1 --> P1["Write SQEs to sqeBuffer_<br/>(Host memory)"]
    P1 --> Q1["Task allocation completed<br/>Wait for LoadComplete to dispatch in batches"]
    
    %% Non-AutoSplit path
    J -->|No, non-AutoSplit mode| E2["AllocTask()"]
    E2 --> F2["Record to delayRecycleTaskid_"]
    F2 --> G2["Write SQEs directly to the device SQ"]
    G2 --> Q2["Task submitted in real time"]
    
    style A fill:#e1f5ff
    style Q1 fill:#fff3e0
    style Q2 fill:#c8e6c9
    style G1 fill:#e8f5e9
```

**Flow Description**:

| Comparison Item | AutoSplit Mode | Non-AutoSplit Mode |
|--------|----------------|-------------------|
| Capacity check | Check whether curStreamSqeCount is close to 32K | No capacity limit check |
| Slave creation | Automatically create Slave Streams to expand capacity | Not supported |
| SQE storage | Write to the Host sqeBuffer_ | Write directly to the device SQ |
| Submission timing | Dispatched in batches at LoadComplete | Real-time submission |

**Key Mechanisms**:
- `HOST_SQ_MAX_COUNT = 32K`: Maximum capacity of the Host SQE buffer
- `AutoSplitSqContext`: Maintains curStreamSqeCount and the slaveStreams list
- `Slave Stream`: Automatically created when the number of tasks is close to 32K, implementing unlimited queue depth

#### EndGraph Marking Flow

```mermaid
flowchart TD
    A["The user calls aclmdlRIEndTask()"] --> B["Create the EndGraph task"]
    B --> C["Generate the Notify object<br/>endGraphNotify_"]
    C --> D["Apply for NotifyId<br/>the hardware completion notification identifier"]
    
    D --> J{"Does the Stream enable AutoSplit?"}
    
    %% AutoSplit path
    J -->|Yes, AutoSplit mode| E1["Write the EndGraph SQE to sqeBuffer_<br/>(Host memory)"]
    E1 --> F1["EndGraph SQE successfully stored<br/>Wait for LoadComplete to dispatch in batches"]
    
    %% Non-AutoSplit path
    J -->|No, non-AutoSplit mode| E2["Write the EndGraph task directly to SQ"]
    E2 --> F2["EndGraph dispatched successfully"]
    
    style A fill:#e1f5ff
    style F1 fill:#fff3e0
    style F2 fill:#c8e6c9
```

**Flow Description**:

| Step | AutoSplit Mode | Non-AutoSplit Mode |
|------|----------------|-------------------|
| 1 | The user marks the end of task dispatching | The user marks the end of task dispatching |
| 2 | Create the EndGraph task | Create the EndGraph task |
| 3 | Create the Notify object and apply for NotifyId | Create the Notify object and apply for NotifyId |
| 4 | **SQEs are written to the Host Buffer** | The EndGraph task is written to SQ |
| 5 | **Wait for LoadComplete to dispatch in batches** | Dispatched successfully immediately |
| 6 | The hardware triggers the Notify Signal during execution | The hardware triggers the Notify Signal during execution |

#### Model LoadComplete Flow

```mermaid
flowchart TD
    A["The user calls aclmdlRIBuildEnd()"] --> B["Trigger LoadComplete"]
    
    B --> C{"Is AutoSplitSq enabled?"}
    
    %% AutoSplit path (detailed flow)
    C -->|Yes| D1["BuildSqCqForAutoSplit()"]
    D1 --> E1["Traverse StreamList_<br/>(Master + Slave Streams)"]
    E1 --> F1["AllocAutoSplitSqAddr()<br/>Allocate SQ/CQ for each Stream"]
    F1 --> G1["Build modelSwitchInfo_<br/>recording stream_id, sq_id, sq_depth"]
    G1 --> H1["SqSwitchStreamBatch()<br/>Switch Streams to SQ in batches"]
    H1 --> I1["SendSqe()<br/>Dispatch SQEs to the device SQ in batches"]
    I1 --> J1["Traverse StreamList_ and execute EnterBindStream()<br/>to establish hardware binding relationships"]
    J1 --> K1["ConfigSqTail()<br/>Configure the SQ Tail pointer"]
    K1 --> L1["SetIsTsBind(true)<br/>Mark the Stream as bound to the TS"]
    L1 --> M1["isModelComplete_=true"]
    M1 --> P["Model loading completed<br/>The model can be executed"]
    
    %% Non-AutoSplit path
    C -->|No| D2["Traverse the Model StreamList_"]
    D2 --> E2["Dispatch the maintenance task for each Stream"]
    E2 --> G2["Dispatch SQEs to the device SQ"]
    G2 --> I2["Record the SQ Tail"]
    I2 --> M2["isModelComplete_=true"]
    M2 --> P
    
    style A fill:#e1f5ff
    style P fill:#c8e6c9
```

**Flow Description**:

| Step | AutoSplit Mode | Non-AutoSplit Mode |
|------|----------------|-------------------|
| 1 | BuildSqCqForAutoSplit() | Traverse StreamList_ directly |
| 2 | Allocate SQ/CQ for all Streams (including Slaves) | SQ/CQ was already allocated at creation |
| 3 | Build modelSwitchInfo_ | Not required |
| 4 | Switch in batches by SqSwitchStreamBatch | Not required |
| 5 | Dispatch SQEs in batches by SendSqe | Dispatch SQEs |
| 6 | **EnterBindStream establishes the hardware binding** | **The hardware binding is already established** |
| 7 | SQ Tail |Configure SQ Tail |
| 8 | SetIsTsBind(true) | Not required |
| 9 | isModelComplete_=true | isModelComplete_=true |

**Key Differences**: In AutoSplit mode, LoadComplete requires:
1. Dynamically allocating SQ/CQ resources
2. Switching Streams to SQ in batches
3. Establishing hardware binding relationships (EnterBindStream)
4. Marking Streams as bound to the TS (SetIsTsBind)

#### Model Execution Flow

```mermaid
flowchart TD
    A["The user calls aclmdlRIExecute()"] --> B["Trigger model execution"]
    
    B --> D["Obtain the execution flow<br/>(use the default or specified Stream)"]
    D --> E["Check the model state"]
    
    E --> F{"Has the model completed LoadComplete?"}
    F -->|No| G["Return an error<br/>The model is not ready"]
    F -->|Yes| H["Create the ExecuteTask"]
    
    H --> J["Submit the ExecuteTask to the device"]
    
    J --> K["Write to SQ: MODEL_EXECUTE"]
    K --> L["The hardware receives the execution instruction"]
    L --> M["Activate headStreams_<br/>starting from the entry Stream"]
    
    M --> N["The hardware scheduler reads SQEs from SQ"]
    N --> O["Execute tasks and compute tasks one by one"]
    
    O --> P["Execute until the EndGraph task"]
    P --> Q["Trigger the Notify Signal"]
    Q --> S["The Host waits for completion"]
    S --> T["Call NtyWait to wait for the Notify"]
    T --> U["Wait for the hardware to return the completion signal"]
    
    U --> V{"Is the completion signal received?"}
    V -->|Success| W["Stream synchronization completed"]
    V -->|Timeout| X["Return a timeout error"]
    
    W --> Y["Poll the CQ status"]
    Y --> Z["Confirm that all tasks are complete"]
    Z --> AA["Model execution completed<br/>Return success"]
    
    style A fill:#e1f5ff
    style G fill:#ffcdd2
    style X fill:#ffcdd2
    style AA fill:#c8e6c9
```

**Flow Description**:

| Step | Description | Difference Between AutoSplit and Non-AutoSplit |
|------|------|------------------------------|
| 1 | The user calls Execute to trigger model execution | None |
| 2 | Prepare the execution environment and obtain the execution Stream | None |
| 3 | Check the model state to ensure LoadComplete is complete | None |
| 4 | Create the ExecuteTask and set execution parameters | None |
| 5 | Submit the ExecuteTask to the device and write to SQ | None |
| 6 | The hardware TS receives the execution instruction and activates headStreams_ | None |
| 7 | **The TS reads SQEs from SQ** | **Difference in the SQE source** |
| 8 | AICore/AIVector executes computation tasks | None |
| 9 | Execute until the EndGraph task and trigger the Notify Signal | None |
| 10 | The Host waits for completion (NtyWait) | None |
| 11 | After the completion signal is received, poll the CQ status | None |
| 12 | Confirm that all tasks are complete and return success | None |

**SQE Source Difference Description**:
- **AutoSplit mode**: SQEs are dispatched in batches from the Host sqeBuffer_ to the device SQ during LoadComplete
  - Written to the Host Buffer at task submission (deferred submission)
  - All SQEs are dispatched in one batch at LoadComplete
  - Supports unlimited queue depth (expanded by Slave Streams)
  
- **Non-AutoSplit mode**: SQEs are directly written to the device SQ at task submission
  - Directly written to the device SQ at task submission (real-time submission)
  - Dispatched immediately when EndGraph is marked
  - Fixed queue depth

**Unified Execution Phase**: In either mode, all SQEs already reside in the device SQ at execution time. The hardware TS reads and executes them directly from SQ, so the flow is completely identical.

#### Label Control Flow Setting Flow

```mermaid
flowchart TD
    A["The user creates a Label"] --> B["Apply to the Model for a LabelId"]
    B --> C["The Model allocates a unique LabelId"]
    C --> D["Record to labelMap_<br/>LabelId → Label object"]
    
    D --> E["The Label is bound to the Model"]
    E --> F["Set the Stream hosting the Label"]
    
    F --> G["The user calls Label::Set()"]
    G --> H["Set a jump point on the Stream"]
    H --> I["Record the current position to devDstAddr_<br/>the hardware jump target address"]
    I --> J["Generate the SetLabel SQE"]
    J --> K["Write SQEs to SQ"]
    K --> L["Jump point setting completed"]
    
    style A fill:#e1f5ff
    style L fill:#c8e6c9
```

**Flow Description**:
1. The user creates a Label and applies to the Model for a unique LabelId.
2. The Model allocates the ID through LabelAllocator and records the mapping relationship.
3. The Label is bound to the Model and Stream.
4. The user calls Label::Set to set the jump target point on the Stream.
5. The current position is recorded to the device-side address (devDstAddr_).
6. The SetLabel SQE is generated and written to the Stream cache.
7. Jump point setting is complete, waiting for subsequent jumps.

#### Label Control Flow Jump Flow

```mermaid
flowchart TD
    A["The user calls LabelSwitch"] --> B["Prepare the jump instruction"]
    B --> C["Obtain the target Label information"]
    
    C --> D["Read the devDstAddr_ of the Label<br/>the target jump address"]
    D --> E["Generate the LabelSwitch SQE (the SQE contains the target address)"]
    
    E --> F["Write to the SQ of the current Stream"]
    F --> G["The hardware executes to the Switch operation"]
    G--> H["Jump to the target Stream"]
    H --> I["Jump completed"]
    
    style A fill:#e1f5ff
```

**Flow Description**:
1. The user calls the LabelSwitch API to initiate a jump instruction.
2. Obtain the device-side address of the target Label (devDstAddr_).
3. Generate the LabelSwitch SQE containing the target jump address.
4. Write it to the SQ of the current Stream.
5. The hardware TS executes to the Switch operation and jumps to the target position.

#### Model Destruction Flow

```mermaid
flowchart TD
    A["The user calls aclmdlRIDestroy()"] --> C["Release Notify resources"]

    C --> D["Delete endGraphNotify_"]
    D --> E["Release device memory"]
    
    E --> F["Clean up argLoaderRecord_<br/>and release parameter handles"]
    F --> G["Clean up dmaAddrRecord_<br/>and release DMA addresses"]
    G --> H["Unbind all Labels"]
    
    H --> I["Traverse labelMap_<br/>and remove the Label-Model relationships"]
    I --> J["Release LabelAllocator"]
    J --> K["Create the destruction task"]
    
    K --> L["Submit ModelDestroyTask"]
    L --> M["Notify the hardware to destroy the model"]
    M --> N["The hardware confirms the destruction<br/>and returns a CQE"]
    
    N --> O["Clean up the Model object"]
    O --> P["Remove the Model from the Context"]
    P --> Q["Model destruction completed"]
    
    style A fill:#e1f5ff
    style Q fill:#c8e6c9
```

**Flow Description**:
1. The user calls Destroy to trigger model destruction.
2. Release Notify resources and delete endGraphNotify_.
3. Release device memory and clean up the parameter handle records.
4. Release the DMA address records.
5. Unbind all Labels and remove their relationships with the Model.
6. Release the LabelAllocator resources.
7. Create the destruction task and notify the hardware to destroy the model.
8. The hardware confirms the destruction and returns a CQE.
9. Clean up the Model object and remove it from the Context.
10. Model destruction is complete and all resources are released.

### 4.2 Details of Core Mechanisms

#### Model Container Management Mechanism

**Design Idea**: As the container of a computation graph, the Model manages all bound Streams and Labels in a unified manner, implementing batch task dispatching and execution entry control.

```mermaid
graph TB
    subgraph ModelManagement["Model container management"]
        StreamBinding["Stream binding management<br/>streams_: all Streams<br/>headStreams_: entry Streams"]
        LabelMgmt["Label control flow management<br/>labelMap_: Label mapping<br/>labelAllocator_: ID allocation"]
        ArgMgmt["Parameter memory management<br/>argLoaderRecord_: parameter handles"]
        ExecMgmt["Execution control<br/>endGraphNotify_: completion notification<br/>isModelComplete_: state flag"]
    end
    
    Model["Model container"]
    
    Model --> StreamBinding
    Model --> LabelMgmt
    Model --> ArgMgmt
    Model --> ExecMgmt
    
    StreamBinding -->|"Batch dispatching"| SQE["Batch SQE dispatch<br/>StreamTaskFill"]
    StreamBinding -->|"Entry activation"| Head["Execution start point<br/>headStreams_"]
    
    LabelMgmt -->|"ID allocation"| LabelId["LabelId<br/>Unique identifier"]
    LabelMgmt -->|"Jump control"| Jump["Stream jumps<br/>Cross-stream control"]
    
    ExecMgmt -->|"Completion notification"| Notify["Notify wait<br/>NtyWait"]
    ExecMgmt -->|"State check"| Ready["Readiness check<br/>LoadComplete"]
```

**Mechanism Description**:
- **Stream binding management**: Maintains the list of all Streams, with headStreams_ as the execution start point
- **Label control flow management**: Allocates Label IDs and manages jump relationships
- **Parameter memory management**: Records task parameter handles to avoid repeated allocation
- **Execution control**: The Notify mechanism implements asynchronous waiting, and state flags ensure the execution order

#### Stream Task Queue Mechanism

**Design Idea**: As the task queue, the Stream caches SQEs and supports task reclamation and automatic SQ splitting.

```mermaid
graph TB
    subgraph StreamQueue["Stream task queue"]
        TaskCache["Task cache<br/>delayRecycleTaskid_<br/>Task ID list"]
        SQEBuffer["SQE buffer<br/>sqeBuffer_<br/>Task descriptors"]
        PosMap["Position mapping<br/>posToTaskIdMap_<br/>Position → task"]
        AutoSplit["Auto splitting<br/>AutoSplitSqContext<br/>Master/Slave"]
    end
    
    Submit["Task submission"]
    
    Submit --> TaskCache
    TaskCache --> SQEBuffer
    SQEBuffer --> PosMap
    
    TaskCache -->|"Cached count"| Count["Task count<br/>curStreamSqeCount"]
    Count -->|"Exceeds 32K"| AutoSplit
    AutoSplit -->|"Create a Slave"| Slave["Slave Stream"]
    AutoSplit -->|"Master management"| Master["Master Stream"]
    
    SQEBuffer -->|"Batch dispatching"| Batch["LoadComplete<br/>Batch dispatching"]
    PosMap -->|"Task reclamation"| Recycle["Task reclamation<br/>TaskReclaim"]
```

**Mechanism Description**:
- **Task cache**: delayRecycleTaskid_ records task IDs and waits for batch dispatching
- **SQE buffer**: sqeBuffer_ stores task descriptors, ready to be written to the hardware SQ
- **Position mapping**: posToTaskIdMap_ records the correspondence between SQE positions and tasks
- **Auto splitting**: When tasks exceed 32K, a Slave Stream is automatically created to expand capacity

#### Label Control Flow Jump Mechanism

**Design Idea**: The Label implements cross-Stream jumps and loop control, achieving hardware-level jumps through device-side addresses.

```mermaid
graph TB
    subgraph LabelAlloc["Label allocation"]
        Request["The user applies for a Label"]
        Alloc["The Model allocates the ID"]
        Record["Record to labelMap_"]
    end
    
    subgraph LabelSet["Label setting"]
        ChooseStream["Select the target Stream"]
        RecordPos["Record the current position"]
        DevAddr["Set devDstAddr_<br/>the device jump address"]
    end
    
    subgraph LabelGoto["Label jump"]
        GetAddr["Read devDstAddr_"]
        GenSQE["Generate the Label Switch SQE"]
        HWJump["Hardware jump execution"]
    end
    
    Request --> Alloc --> Record
    Record --> ChooseStream --> RecordPos --> DevAddr
    
    DevAddr --> GetAddr --> GenSQE --> HWJump
    
    HWJump -->|"Same Stream"| Loop["Loop control"]
    HWJump -->|"Cross-Stream"| Switch["Cross-stream switching"]
    
    style Request fill:#e1f5ff
    style HWJump fill:#c8e6c9
```

**Mechanism Description**:
- **Label allocation**: The Model allocates a unique ID through LabelAllocator
- **Label setting**: Records the jump position on the target Stream and sets the device-side address
- **Label jump**: Reads the device address, generates the jump SQE, and the hardware executes the jump
- **Control flow implementation**: Supports loops (same Stream) and cross-Stream task switching

#### Notify Completion Notification Mechanism

**Design Idea**: Notify implements hardware completion notification, and the Host obtains the execution result by waiting on the Notify.

```mermaid
sequenceDiagram
    participant Model as Model
    participant EndGraph as EndGraphTask
    participant Notify as endGraphNotify_
    participant Driver as Driver
    participant HW as Hardware TS
    
    %% EndGraph creates the Notify
    Model->>EndGraph: rtEndGraph(model, stream)
    EndGraph->>Notify: Create the Notify object
    Notify->>Driver: AllocNotifyId()
    Driver->>HW: Apply for notifyId
    HW-->>Driver: notifyId
    Driver-->>Notify: notifyId
    Notify-->>Model: endGraphNotify_
    
    %% Write the EndGraph task during execution
    Model->>EndGraph: Execute()
    EndGraph->>Driver: SubmitTask(EndGraphTask)
    Driver->>HW: SQE: END_GRAPH<br/>notifyId=notifyId_
    HW->>HW: Execute all preceding tasks
    HW->>HW: Execute the EndGraph task
    HW->>HW: Signal Notify<br/>notifyId ← value++
    
    %% The Host waits on the Notify
    Model->>Notify: NtyWait(endGraphNotify_, stream)
    Notify->>Driver: Notify::Wait()
    Driver->>HW: Poll Notify Value<br/>MSG: NOTIFY_POLL
    HW-->>Driver: notifyValue
    Driver-->>Notify: value matched
    Notify-->>Model: wait success
    Model->>Model: Execution completed
```

**Mechanism Description**:
- **Notify creation**: The EndGraph task applies for a NotifyId and binds it to the Model
- **Notify wait**: The Host polls the Notify value through NtyWait
- **Notify trigger**: When the hardware executes to the EndGraph, it signals the Notify and updates the value
- **Completion confirmation**: When the Host detects a value match, it confirms that execution is complete

### 4.3 Module Responsibility Division

The Model module is divided by function into sub-modules such as the core container, task management, API layer, and auxiliary tools. Each sub-module has clear responsibilities and collaborates to complete full lifecycle model management.

#### Core Container Modules

| Module Name | Core Responsibility | Code Location | Main Functions |
|----------|----------|----------|----------|
| **Model core class** | Computation graph container that manages Streams/Labels/Notifies in a unified manner | `src/runtime/core/inc/model/model.hpp`<br/>`src/runtime/feature/model/model.cc` | • Binds/unbinds Streams<br/>• Allocates/releases Labels<br/>• Executes models synchronously/asynchronously<br/>• Dispatches SQEs in batches<br/>• Manages argLoaderRecord |
| **Model C API** | External C-style API wrapper | `src/runtime/api/api_c_model.cc` | • rtModelCreate<br/>• rtModelDestroy<br/>• rtModelBindStream<br/>• rtModelExecute<br/>• rtEndGraph<br/>• rtModelLoadComplete |

#### Task Management Modules

| Task Type | Task Responsibility | Code Location | Trigger Timing |
|----------|----------|----------|----------|
| **ModelExecuteTask** | Triggers model execution and activates headStreams | `src/runtime/core/src/task/task_info/model/model_execute_task.cc`<br/>`src/runtime/core/src/task/task_info/model/model_execute_task_v100.cc`<br/>`src/runtime/core/src/task/task_info/model/model_execute_task_v200_base.cc` | When Execute/ExecuteAsync is called |
| **ModelMaintainceTask** | Maintains the relationship between Streams and the Model | `src/runtime/core/src/task/task_info/model/model_maintaince_task.cc`<br/>`src/runtime/core/src/task/task_info/model/model_maintaince_task_v100.cc`<br/>`src/runtime/core/src/task/task_info/model/model_maintaince_task_v200_base.cc` | BindStream/UnbindStream<br/>and at LoadComplete |
| **ModelGraphTask** | Marks EndGraph and creates the Notify | `src/runtime/core/src/task/task_info/model/model_graph_task.cc`<br/>`src/runtime/core/src/task/task_info/model/model_graph_task_v100.cc`<br/>`src/runtime/core/src/task/task_info/model/model_graph_task_v200_base.cc` | When rtEndGraph is called |

#### Auxiliary Tool Modules

| Tool Module | Auxiliary Responsibility | Code Location | Serves |
|----------|----------|----------|----------|
| **LabelAllocator** | Label ID allocator | `src/runtime/core/inc/launch/label.hpp` | Model Label management |
| **Notify** | Hardware completion notification object | `src/runtime/core/inc/notify/notify.hpp`<br/>`src/runtime/core/src/notify/notify.cc` | EndGraph Notify |

#### API Adaptation Layer

| Adaptation Layer | Adaptation Responsibility | Code Location | Serves |
|----------|----------|----------|----------|
| **ACL API wrapper** | ACL → RT API mapping | `src/acl/aclrt_impl/model_ri.cpp` | User calls to the aclmdlRI APIs |
| **API decorators** | API error handling decoration | `src/runtime/api/impl/api_decorator.cc`| ApiImpl call chain |


### 5 Key File Path Index

| Module Category | File Path | Core Content |
|----------|----------|----------|
| **Model header file** | `src/runtime/core/inc/model/model.hpp` | Model class definitions and data structures |
| **Model implementation** | `src/runtime/feature/model/model.cc` | Core Model implementation |
| **Model C API** | `src/runtime/feature/model/model_c.cc` | C-style API implementation |
| **Model Execute Task** | `src/runtime/core/src/task/task_info/model/model_execute_task.cc` | Execution task implementation |
| **Model Execute Task V100** | `src/runtime/core/src/task/task_info/model/model_execute_task_v100.cc` | V100 version adaptation |
| **Model Execute Task V200** | `src/runtime/core/src/task/task_info/model/model_execute_task_v200_base.cc` | V200 version adaptation |
| **Model Maintaince Task** | `src/runtime/core/src/task/task_info/model/model_maintaince_task.cc` | Maintenance task implementation |
| **ACL API header file** | `include/external/acl/acl_rt.h` | External ACL API definitions |
| **ACL API implementation** | `src/acl/aclrt_impl/model_ri.cpp` | ACL API implementation (aclmdlRI series) |
