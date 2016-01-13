package sobseq;

import com.maxeler.maxcompiler.v2.build.EngineParameters;
import com.maxeler.maxcompiler.v2.kernelcompiler.Kernel;
import com.maxeler.maxcompiler.v2.managers.standard.Manager;
import com.maxeler.maxcompiler.v2.managers.standard.Manager.IOType;

public class SobSeqManager {

	private static final String s_kernelName = "SobSeqKernel";

	public static void main(String[] args) {
		SobSeqEngineParameters params = new SobSeqEngineParameters(args);
		Manager manager = new Manager(params);
		Kernel kernel   = new SobSeqKernel(manager.makeKernelParameters(s_kernelName));
		manager.setKernel(kernel);
		manager.setIO(
			link("ix",   IODestination.CPU),
			link("iv",   IODestination.CPU),
			link("fac", IODestination.CPU));

		manager.createSLiCinterface(interfaceDefault());
		
		configBuild(manager, params);
		
		manager.build();
	}

	private static EngineInterface interfaceDefault() {
		EngineInterface engine_interface = new EngineInterface();
		CPUTypes   uLong = CPUTypes.INT32;
		CPUTypes   uFloat = CPUTypes.FLOAT; 
		int        size = type.sizeInBytes();

		InterfaceParam  a    = engine_interface.addParam("A", CPUTypes.INT);
		InterfaceParam  N    = engine_interface.addParam("N", CPUTypes.INT);

		engine_interface.setScalar(s_kernelName, "a", a);
		engine_interface.setTicks(s_kernelName, N);

		engine_interface.setStream("ix",   uLong, N * size);
		engine_interface.setStream("iv",   uLong, N * size);

		engine_interface.setStream("ixOut", uLong, N * size);
		engine_interface.setStream("x", uFloat, N * size);
		
		return engine_interface;
	}
	
	private static void configBuild(Manager manager, CpuStreamEngineParameters params) {
		manager.setEnableStreamStatusBlocks(false);
		BuildConfig buildConfig = manager.getBuildConfig();
		buildConfig.setMPPRCostTableSearchRange(params.getMPPRStartCT(), params.getMPPREndCT());
		buildConfig.setMPPRParallelism(params.getMPPRThreads());
		buildConfig.setMPPRRetryNearMissesThreshold(params.getMPPRRetryThreshold());
	}
}