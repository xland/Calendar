export class config{
    appName:string //english
    publisher:string
    version:string
    sing:string //todo
    resource:{
        icon:string
        bannerImg:string|string[]
        download:{
            url:string
            needRelease:boolean
            targetPath:string //appdata or installPath
        }[]
        resource:{
            path:string
            needRelease:boolean
            targetPath:string
        }[]
    }
    window:{
        title:string
        centerScreen:boolean
        x:number
        y:number
        shadow:boolean
        borderWidth:number
        borderColor:number
        width:number
        height:number
        background:string
        progressor:{
            left:number
            right:number
            top:number
            bottom:number
            width:number
            height:number
            bgColor:string
            thumbColor:string
            animateType:string //todo
            zIndex:number
        }
        btnInstall:{
            left:number
            right:number
            top:number
            bottom:number
            width:number
            height:number
            bgColor:string
            hoverBgColor:string
            color:string
            hoverColor:string
            text:string
            fontSize:number
            textUnderline:boolean
            hoverTextUnderline:boolean
            zIndex:number
        }
        btnMinimize:{
            left:number
            right:number
            top:number
            bottom:number
            width:number
            height:number
            bgColor:string
            hoverBgColor:string
            zIndex:number
        }
        btnClose:{
            left:number
            right:number
            top:number
            bottom:number
            width:number
            height:number
            bgColor:string
            hoverBgColor:string
            zIndex:number
        }
        checkboxAcceptLicence:{
            visible:boolean 
            left:number
            right:number
            top:number
            bottom:number
            width:number
            height:number
            color:string
            hoverColor:string
            text:string
            fontSize:number
            textUnderline:boolean
            hoverTextUnderline:boolean
            zIndex:number
        }
        checkboxStartAppWhenReady:{
            visible:boolean 
            left:number
            right:number
            top:number
            bottom:number
            width:number
            height:number
            color:string
            hoverColor:string
            text:string
            fontSize:number
            textUnderline:boolean
            hoverTextUnderline:boolean
            zIndex:number
        }
        checkboxAutoStartWithSystem:{ //todo 是否有必要，Electron有这个能力
            visible:boolean
            left:number
            right:number
            top:number
            bottom:number
            width:number
            height:number
            color:string
            hoverColor:string
            text:string
            fontSize:number
            textUnderline:boolean
            hoverTextUnderline:boolean
            zIndex:number
        }
        otherBtn:{
            left:number
            right:number
            top:number
            bottom:number
            width:number
            height:number
            bgColor:string
            hoverBgColor:string
            color:string
            hoverColor:string
            text:string
            fontSize:number
            textUnderline:boolean
            hoverTextUnderline:boolean
            zIndex:number
        }[]
    }
    install:{
        installPath:string //ProgramFiles,AppDataLocal
        userType:string //CurrentUser,EveryOne
        customInstallPath:boolean
        autoStartWithSystem:boolean
        killProcessName:string[]
        deleteFileWhenExists:string[] //todo是否可以合并成一个
        deletePathWhenExists:string[]
        installSilence:boolean
        installReady:{
            startApp:boolean
            createDesktopIcon:boolean
            createStartMenuIcon:boolean
            createTaskbarIcon:boolean
        }
    }
    uninstall:{
        removeUserData:boolean
        uninstallReady:{
            openUrl:string
        }        
    }
}