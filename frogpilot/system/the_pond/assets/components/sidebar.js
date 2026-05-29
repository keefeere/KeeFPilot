import { html, reactive } from "https://esm.sh/@arrow-js/core@1.0.6";
import { Link } from "/assets/components/router.js";
import { upperFirst, hideSidebar } from "/assets/js/utils.js";

const MenuItems = {
  home: [
    { name: "Home", link: "/", icon: "bi-house-fill" },
  ],
  navigation: [
    { name: "Manage Keys", link: "/manage_navigation_keys", icon: "bi-key-fill" },
    { name: "Set Destination", link: "/set_navigation_destination", icon: "bi-globe-americas" },
  ],
  recordings: [
    { name: "Dashcam Routes", link: "/dashcam_routes", icon: "bi-camera-reels" },
    { name: "Screen Recordings", link: "/screen_recordings", icon: "bi-record-circle" },
  ],
  tailscale: [
    { name: "Tailscale", link: "/manage_tailscale", icon: "bi-wifi" },
  ],
  tools: [
    { name: "Download Speed Limits", link: "/download_speed_limits", icon: "bi-download" },
    { name: "Error Logs", link: "/manage_error_logs", icon: "bi-exclamation-triangle" },
    { name: "Lock/Unlock Doors", link: "/lock_or_unlock_doors", icon: "bi-door-closed" },
    { name: "Theme Maker", link: "/theme_maker", icon: "bi-palette-fill" },
    { name: "Tmux Log", link: "/manage_tmux", icon: "bi-terminal" },
    { name: "Toggles", link: "/manage_toggles", icon: "bi-toggle-on" },
    { name: "Toyota Security Keys", link: "/tsk_manager", icon: "bi-key-fill" },
  ],
};

const state = reactive({
  doorsVisible: false,
  isDoorsFetched: false,
  isTSKFetched: false,
  tskVisible: false
});

fetchSidebarAvailability();

export function Sidebar(routerState) {
  function navigate() {
    window.scrollTo(0, 0);
    hideSidebar();
  }

  return html`
    <div id="sidebarRoot">
      <div id="sidebarUnderlay" class="hidden" @click="${hideSidebar}"></div>
      <div id="sidebar" class="sidebar">
        <div>
          <div class="title">
            <img class="logo" src="/assets/images/main_logo.png" alt="FrogPilot logo" />
            <div class="title_text sidebar_header">
              <p>The Pond</p>
              <a href="https://github.com/Aidenir">by&nbsp;Aidenir</a>
            </div>
          </div>
          <hr />
          ${() => {
            const currentPath = routerState?.activePathFull ?? window.location.pathname;

            return Object.entries(MenuItems).map(([section, links]) => {
              const visibleLinks = links.filter(link => {
                if (link.name === "Lock/Unlock Doors" && !state.doorsVisible) {
                  return false;
                }

                if (link.name === "Toyota Security Keys" && !state.tskVisible) {
                  return false;
                }

                return true;
              });

              if (visibleLinks.length === 0) {
                return "";
              }

              return html`
                <div class="sidebar_widget">
                  <ul class="menu_section">
                    <li>
                      <span class="section-title">${upperFirst(section)}</span>
                      <ul id="${section}">
                        ${visibleLinks.map(link => {
                          const classList = link.link === currentPath ? "active" : "";
                          const iconClass = `bi ${link.icon}`;
                          const content = html`
                            <div class="menu-item-link">
                              <i class="${iconClass}"></i>
                              <span>${upperFirst(link.name)}</span>
                            </div>
                          `;

                          return html`
                            <li class="${classList}">
                              ${Link(link.link, content, navigate)}
                            </li>
                          `;
                        })}
                      </ul>
                    </li>
                  </ul>
                </div>
              `;
            });
          }}
        </div>
      </div>
    </div>`;
}

async function fetchSidebarAvailability() {
  if (!state.isDoorsFetched) {
    state.isDoorsFetched = true;
    try {
      const response = await fetch("/api/doors_available");
      const data = await response.json();
      state.doorsVisible = data.result;
    } catch (e) {
      console.error("Failed to fetch door availability:", e);
    }
  }

  if (!state.isTSKFetched) {
    state.isTSKFetched = true;
    try {
      const response = await fetch("/api/tsk_available");
      const data = await response.json();
      state.tskVisible = data.result;
    } catch (e) {
      console.error("Failed to fetch TSK availability:", e);
    }
  }
}

function setupMenuButton() {
  const button = document.getElementById("menu_button");
  const sidebar = document.getElementById("sidebar");
  const underlay = document.getElementById("sidebarUnderlay");

  if (!button || !sidebar || !underlay) {
    return;
  }

  button.addEventListener("click", () => {
    const isVisible = sidebar.classList.toggle("visible");
    underlay.classList.toggle("hidden", !isVisible);
    document.documentElement.classList.toggle("no_scroll", isVisible);
  });
}

document.addEventListener("DOMContentLoaded", setupMenuButton, false);
