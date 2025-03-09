#ifndef ASR_PRO_PLUGIN_MANAGER_H
#define ASR_PRO_PLUGIN_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "plugin_api.h"

namespace asrpro {
namespace plugin {

class PluginManager {
public:
    PluginManager();
    ~PluginManager();

    // Plugin yönetimi
    bool loadPlugin(const std::string& path);
    bool unloadPlugin(const std::string& name);
    
    // Plugin erişimi
    IPlugin* getPlugin(const std::string& name);
    std::vector<std::string> getLoadedPlugins() const;

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace plugin
} // namespace asrpro

#endif // ASR_PRO_PLUGIN_MANAGER_H