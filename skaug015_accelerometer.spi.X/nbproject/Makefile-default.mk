#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=${DISTDIR}/skaug015_accelerometer.spi.X.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=a
DEBUGGABLE_SUFFIX=
FINAL_IMAGE=${DISTDIR}/skaug015_accelerometer.spi.X.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=accel_define.c accel_read_x.c accel_read_y.c accel_read_z.c accel_setup.c spi2_read_register.c spi2_setup.c spi2_write_register.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/accel_define.o ${OBJECTDIR}/accel_read_x.o ${OBJECTDIR}/accel_read_y.o ${OBJECTDIR}/accel_read_z.o ${OBJECTDIR}/accel_setup.o ${OBJECTDIR}/spi2_read_register.o ${OBJECTDIR}/spi2_setup.o ${OBJECTDIR}/spi2_write_register.o
POSSIBLE_DEPFILES=${OBJECTDIR}/accel_define.o.d ${OBJECTDIR}/accel_read_x.o.d ${OBJECTDIR}/accel_read_y.o.d ${OBJECTDIR}/accel_read_z.o.d ${OBJECTDIR}/accel_setup.o.d ${OBJECTDIR}/spi2_read_register.o.d ${OBJECTDIR}/spi2_setup.o.d ${OBJECTDIR}/spi2_write_register.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/accel_define.o ${OBJECTDIR}/accel_read_x.o ${OBJECTDIR}/accel_read_y.o ${OBJECTDIR}/accel_read_z.o ${OBJECTDIR}/accel_setup.o ${OBJECTDIR}/spi2_read_register.o ${OBJECTDIR}/spi2_setup.o ${OBJECTDIR}/spi2_write_register.o

# Source Files
SOURCEFILES=accel_define.c accel_read_x.c accel_read_y.c accel_read_z.c accel_setup.c spi2_read_register.c spi2_setup.c spi2_write_register.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/skaug015_accelerometer.spi.X.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX470F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/accel_define.o: accel_define.c  .generated_files/flags/default/f367f8a5e9538cb03657b2b795272270d03f96e4 .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/accel_define.o.d 
	@${RM} ${OBJECTDIR}/accel_define.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel_define.o.d" -o ${OBJECTDIR}/accel_define.o accel_define.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/accel_read_x.o: accel_read_x.c  .generated_files/flags/default/9f0bf57ae89f68c90a242acb1b8cf1c581544cde .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/accel_read_x.o.d 
	@${RM} ${OBJECTDIR}/accel_read_x.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel_read_x.o.d" -o ${OBJECTDIR}/accel_read_x.o accel_read_x.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/accel_read_y.o: accel_read_y.c  .generated_files/flags/default/25a3904f048d9f75a6344183e957553159f0da25 .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/accel_read_y.o.d 
	@${RM} ${OBJECTDIR}/accel_read_y.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel_read_y.o.d" -o ${OBJECTDIR}/accel_read_y.o accel_read_y.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/accel_read_z.o: accel_read_z.c  .generated_files/flags/default/27cc1beee26122b2f17f39ab296818dd78d381d6 .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/accel_read_z.o.d 
	@${RM} ${OBJECTDIR}/accel_read_z.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel_read_z.o.d" -o ${OBJECTDIR}/accel_read_z.o accel_read_z.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/accel_setup.o: accel_setup.c  .generated_files/flags/default/d7ccb9bab5355bbec37b2a13cc8b0c7a0c4a9dcd .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/accel_setup.o.d 
	@${RM} ${OBJECTDIR}/accel_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel_setup.o.d" -o ${OBJECTDIR}/accel_setup.o accel_setup.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/spi2_read_register.o: spi2_read_register.c  .generated_files/flags/default/f712a66fbd45d6d74c9ac6a8941ac7ceaa1e475 .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spi2_read_register.o.d 
	@${RM} ${OBJECTDIR}/spi2_read_register.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spi2_read_register.o.d" -o ${OBJECTDIR}/spi2_read_register.o spi2_read_register.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/spi2_setup.o: spi2_setup.c  .generated_files/flags/default/dae5d8b6e4ac7de6d17e7be6a05cc82567ff8eac .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spi2_setup.o.d 
	@${RM} ${OBJECTDIR}/spi2_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spi2_setup.o.d" -o ${OBJECTDIR}/spi2_setup.o spi2_setup.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/spi2_write_register.o: spi2_write_register.c  .generated_files/flags/default/a7c50239022bdf53d890b75efedd4e3f38af6af7 .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spi2_write_register.o.d 
	@${RM} ${OBJECTDIR}/spi2_write_register.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spi2_write_register.o.d" -o ${OBJECTDIR}/spi2_write_register.o spi2_write_register.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/accel_define.o: accel_define.c  .generated_files/flags/default/4b223c55d6a06c54a185eaae3e9d260de5c45560 .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/accel_define.o.d 
	@${RM} ${OBJECTDIR}/accel_define.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel_define.o.d" -o ${OBJECTDIR}/accel_define.o accel_define.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/accel_read_x.o: accel_read_x.c  .generated_files/flags/default/eac557a6d50cb4572b76f7c4570a616e8c4b7eb .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/accel_read_x.o.d 
	@${RM} ${OBJECTDIR}/accel_read_x.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel_read_x.o.d" -o ${OBJECTDIR}/accel_read_x.o accel_read_x.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/accel_read_y.o: accel_read_y.c  .generated_files/flags/default/44c257f57e19bf6998a87ab87b27b500f4840e7e .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/accel_read_y.o.d 
	@${RM} ${OBJECTDIR}/accel_read_y.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel_read_y.o.d" -o ${OBJECTDIR}/accel_read_y.o accel_read_y.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/accel_read_z.o: accel_read_z.c  .generated_files/flags/default/64cdd9141e985a2dd543ebdc15099881796197aa .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/accel_read_z.o.d 
	@${RM} ${OBJECTDIR}/accel_read_z.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel_read_z.o.d" -o ${OBJECTDIR}/accel_read_z.o accel_read_z.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/accel_setup.o: accel_setup.c  .generated_files/flags/default/be84d2e7363decba02680f8d866cd8807258f808 .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/accel_setup.o.d 
	@${RM} ${OBJECTDIR}/accel_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/accel_setup.o.d" -o ${OBJECTDIR}/accel_setup.o accel_setup.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/spi2_read_register.o: spi2_read_register.c  .generated_files/flags/default/7e356ef400ea4bbffdfde7ecbeec884b6ef227cc .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spi2_read_register.o.d 
	@${RM} ${OBJECTDIR}/spi2_read_register.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spi2_read_register.o.d" -o ${OBJECTDIR}/spi2_read_register.o spi2_read_register.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/spi2_setup.o: spi2_setup.c  .generated_files/flags/default/609ff5fb9c1a44b92a3ba7f8a20d480460035838 .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spi2_setup.o.d 
	@${RM} ${OBJECTDIR}/spi2_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spi2_setup.o.d" -o ${OBJECTDIR}/spi2_setup.o spi2_setup.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/spi2_write_register.o: spi2_write_register.c  .generated_files/flags/default/b8f57394bcf7dc7ca2aa8fe07f06242a88dacc75 .generated_files/flags/default/8745ad97b176766356acb69d287b7157ab13b58b
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spi2_write_register.o.d 
	@${RM} ${OBJECTDIR}/spi2_write_register.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/spi2_write_register.o.d" -o ${OBJECTDIR}/spi2_write_register.o spi2_write_register.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: archive
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/skaug015_accelerometer.spi.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  r ${DISTDIR}/skaug015_accelerometer.spi.X.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    
else
${DISTDIR}/skaug015_accelerometer.spi.X.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_AR} $(MP_EXTRA_AR_PRE)  r ${DISTDIR}/skaug015_accelerometer.spi.X.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
